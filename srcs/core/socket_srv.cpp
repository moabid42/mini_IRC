/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket_srv.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 17:01:18 by moabid            #+#    #+#             */
/*   Updated: 2023/01/21 18:03:26 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "socket_srv.hpp"

SocketServer::SocketServer(int port)
{
    // Create a socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        std::cerr << "Error creating socket" << std::endl;
        exit(-1);
    }
    // Fill in the address structure
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = INADDR_ANY;
    // Bind the socket
    if (bind(sockfd, (struct sockaddr *) &server_address, sizeof(server_address)) < 0)
        err_and_ext("Error reading from socket");
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

int SocketServer::accept_connection(std::string password)
{
    socklen_t           client_len;
    struct sockaddr_in  client_address;
    int                 client_sockfd;

    // better way to handle this password ?
    if (password != "myshit")
        err_and_ext("Bitch who are you ?");

    client_sockfd = accept(sockfd, (struct sockaddr *) &client_address, &client_len);
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

Message SocketServer::parse_message(std::string message_str)
{
    Message message;
    // Parse the message string into a Message object
    return message;
}

void SocketServer::process_message(Message message, int client_sockfd)
{

    if (message.command == "JOIN")
    {
        std::string response = "Welcome maybe ?";
        send_message(response, client_sockfd);
    }
    else if (message.command == "PRIVMSG")
    {
        std::string response = "some shit here";
        send_message(response, client_sockfd);
    }
    // here still have to add more commands ...
    else
    {
        std::string response = "Unknown command";
        send_message(response, client_sockfd);
    }
}

void SocketServer::send_message(std::string message, int client_sockfd)
{
    int n;

    n = write(client_sockfd, message.c_str(), message.length());
    if (n < 0)
        err_and_ext("Error writing to socket");
}