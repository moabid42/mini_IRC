/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket_srv.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 17:01:18 by moabid            #+#    #+#             */
/*   Updated: 2023/01/22 11:32:07 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "socket_srv.hpp"

SocketServer::SocketServer(int port, std::string password)
{
    // Create a socket
    _password = password;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        err_and_ext("Error creating socket");
    // Fill in the address structure
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = INADDR_ANY;
    // Bind the socket
    if (bind(sockfd, (struct sockaddr *) &server_address, sizeof(server_address)) < 0)
        err_and_ext("Error binding the socket");
    authenticated_clients = std::unordered_map<int, bool>();
}

SocketServer::~SocketServer()
{
    close(sockfd);
}

//////////// Member Functions ///////////

void SocketServer::start()
{
    listen(sockfd, 5);
}

int SocketServer::accept_connection()
{
    socklen_t           client_len;
    struct sockaddr_in  client_address;
    int                 client_sockfd;

    client_sockfd = accept(sockfd, (struct sockaddr *) &client_address, &client_len);
    std::cout << client_sockfd << std::endl;
    if (client_sockfd < 0)
        err_and_ext("Error reading from socket");
    return client_sockfd;
}

void SocketServer::read_write_loop(int client_sockfd)
{
    char buffer[256];
    int n;

    while (1)
    {
        bzero(buffer, 256);
        //maybe use recv ?
        n = read(client_sockfd, buffer, 255);
        if (n < 0)
            err_and_ext("Error reading from socket");
        std::cout << "Received: " << buffer << std::endl;
        // process the mssg here
        std::string message_str(buffer);
        Message message = parse_message(message_str);
        process_message(message, client_sockfd);
    }
}

Message SocketServer::parse_message(const std::string& buffer)
{
    std::string                 prefix, command;
    std::vector<std::string>    parameters;
    std::stringstream           ss(buffer);
    std::string                 first_word;
    
    std::getline(ss, first_word, ' ');
    if (first_word.front() == ':')
    {
        prefix = first_word.substr(1);
        std::getline(ss, command, ' ');
    }
    else
        command = first_word;
    std::string param;
    while (std::getline(ss, param, ' '))
    {
        // params trailing 
        if (param.front() == ':')
        {
            param = param.substr(1);
            std::string temp;
            while (std::getline(ss, temp, ' '))
                param += " " + temp;
            parameters.push_back(param);
            break;
        }
        else
            parameters.push_back(param);
    }
    return Message(prefix, command, parameters);
}

bool SocketServer::check_password(const std::string& password)
{
    return (password == _password);
}

void SocketServer::process_message(Message& message, int client_socket)
{
    if (!authenticated_clients[client_socket])
    {
        if (message.getCommand() == "PASS")
        {
            // Maybe using some hashing for password later ?!
            std::string password = message.getParametersIndex(0);
            if (check_password(password))
            {
                authenticated_clients[client_socket] = true;
                send_message(client_socket, "Authentication Successful\r\n");
            }
            else
                send_message(client_socket, "Invalid password\r\n");
        }
        else
            send_message(client_socket, "Authentication Required\r\n");
    }
    else
    {
        if (message.getCommand() == "JOIN")
        {
            // Handle JOIN command
        }
        else if (message.getCommand() == "PRIVMSG")
        {
            // Handle PRIVMSG command
        }
        else if (message.getCommand() == "QUIT")
        {
            // Handle QUIT command
            authenticated_clients[client_socket] = false;
        }
        else
        {
            // Handle other commands
        }
    }
}

void SocketServer::send_message(int client_sockfd, std::string message)
{
    int n;

    n = write(client_sockfd, message.c_str(), message.length());
    if (n < 0)
        err_and_ext("Error writing to socket");
}