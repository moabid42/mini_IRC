/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket_srv.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 16:17:46 by moabid            #+#    #+#             */
/*   Updated: 2023/01/21 22:36:36 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "irc.hpp"
#include "message.hpp"

class Message;

class SocketServer
{
    private:
        int                             sockfd;
        std::string                     _password;
        struct sockaddr_in              server_address;
        std::unordered_map<int, bool>   authenticated_clients;

    public:
        SocketServer(int port, std::string password);
        ~SocketServer();
    
        void    start();
        int     accept_connection();
        void    read_write_loop(int client_sockfd);
        
        Message parse_message(const std::string& buffer);
        bool    check_password(const std::string& password);
        void    process_message(Message& message, int client_socket);
        void    send_message(int client_sockfd, std::string message);
};