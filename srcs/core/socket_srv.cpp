/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket_srv.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 17:01:18 by moabid            #+#    #+#             */
/*   Updated: 2023/01/23 00:32:28 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "socket_srv.hpp"

SocketServer::SocketServer(int port, std::string password)
{
    // Create a socket
    _password = password;
    _server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (_server_socket < 0)
        err_and_ext("Error creating socket");
    // Fill in the address structure
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = INADDR_ANY;
    // Bind the socket
    if (bind(_server_socket, (struct sockaddr *) &server_address, sizeof(server_address)) < 0)
        err_and_ext("Error binding the socket");
    authenticated_clients = std::map<int, bool>();
    _channels = std::map<std::string, Channel>();
}

SocketServer::~SocketServer()
{
    close(_server_socket);
}

//////////// Member Functions ///////////

void SocketServer::start()
{
    listen(_server_socket, 5);
}

// void    SocketServer::accept_connection()
// {
//     while (1)
//     {
//         socklen_t           client_len;
//         struct sockaddr_in  client_address;
//         int                 client_sockfd;

//         client_sockfd = ::accept(_server_socket, (struct sockaddr *) &client_address, &client_len);
//         if (client_sockfd < 0)
//             err_and_ext("Error accepting connection");
//         authenticated_clients[client_sockfd] = false;
//         std::cout<< "we have " << client_sockfd << std::endl;
//     }
// }

void SocketServer::connect()
{
    struct pollfd   fds[MAX_CLIENTS];
    int             nfds = 1;

    fds[0].fd = _server_socket;
    fds[0].events = POLLIN;
    while (1)
    {
        int ret = poll(fds, nfds, -1);
        if (ret < 0)
        {
            perror("poll");
            continue;
        }
        if (fds[0].revents & POLLIN)
        {
            int client_socket = accept(_server_socket, nullptr, nullptr);
            if (client_socket < 0)
            {
                perror("accept");
                continue;
            }
            fcntl(client_socket, F_SETFL, O_NONBLOCK);
            fds[nfds].fd = client_socket;
            fds[nfds].events = POLLIN;
            nfds++;
        }
        for (int i = 1; i < nfds; i++)
        {
            if (fds[i].revents & POLLIN)
            {
                char buffer[BUFSIZE];
                int n;

                bzero(buffer, BUFSIZE);
                n = recv(fds[i].fd, buffer, 255, 0);
                if (n < 0)
                    err_and_ext("Error reading from socket");
                std::cout << "Received: " << buffer << std::endl;
                // process the mssg here
                std::string message_str(buffer);
                message_str.pop_back();
                Message *message = parse_message(message_str);
                process_message(message, fds[i].fd);
            }
        }
    }
}


Message* SocketServer::parse_message(const std::string& buffer)
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
    return new Message(prefix, command, parameters);
}

bool SocketServer::check_password(const std::string& password)
{
    std::cout << "The password is " << password << "-password " << _password <<std::endl;
    return (password == _password);
}

void SocketServer::process_message(Message *message, int client_socket)
{
    if (!authenticated_clients[client_socket])
    {
        if (message->getCommand() == "PASS")
        {
            // Maybe using some hashing for password later ?!
            std::string password = message->getParametersIndex(0);
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
        // here we have to add the username check function and the NICK command to set the username
        if (username_set() == true)
        {
            if (message->getCommand() == "JOIN")
            {
                std::string channel_name = message->getParametersIndex(0);
                if (_channels.count(channel_name) == 0)
                    _channels[channel_name] = Channel(channel_name);
                // Have to do some changes here so that we add the user only after having the username set 
                _channels[channel_name].addUser(client_socket);
                send_message(client_socket, std::to_string(client_socket));
                send_message(client_socket, "just joined a channel\b");
                send_message(client_socket, channel_name);
                send_message(client_socket, "\r\n");
                
            }
            else if (message->getCommand() == "PRIVMSG")
            {
                // Handle PRIVMSG command
            }
            else if (message->getCommand() == "QUIT")
            {
                // Handle QUIT command
                authenticated_clients[client_socket] = false;
            }
            else
                send_message(client_socket, "Command not Found\r\n");
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

void SocketServer::broadcastMessage(std::string message, Channel* channel)
{
    if(channel)
        for (auto user : channel->getUsers())
            send_message(user.first, message);
}

