/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket_srv.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 16:17:46 by moabid            #+#    #+#             */
/*   Updated: 2023/01/24 11:50:36 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "irc.hpp"
#include "message.hpp"
#include "channel.hpp"

class Message;
class Channel;

class SocketServer
{
    private:
        int                               _server_socket;
        std::string                       _password;
        struct sockaddr_in                server_address;
        std::map<int, std::pair<std::string, std::string> >        authenticated_clients;
        std::map<std::string, Channel>    _channels;

    public:
        SocketServer(int port, std::string password);
        ~SocketServer();
    
        void    start();
        void    connect();
        // void    accept_connection();
        
        Message *parse_message(const std::string& buffer);
        bool    check_password(const std::string& password);
        void    process_message(Message *message, int client_socket);
        void    send_message(int client_sockfd, std::string message);
        void    broadcastMessage(std::string message, Channel* channel);
};
