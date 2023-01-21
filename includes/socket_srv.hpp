/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket_srv.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 16:17:46 by moabid            #+#    #+#             */
/*   Updated: 2023/01/21 17:45:43 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "irc.hpp"
#include "message.hpp"

class Message;

class SocketServer
{
    private:
        int sockfd;
        struct sockaddr_in server_address;

    public:
        SocketServer(int port);
        ~SocketServer();
    
        void    start();
        int     accept_connection(std::string password);
        void    read_write_loop(int client_sockfd);
        
        Message parse_message(std::string message_str);
        void    process_message(Message message, int client_sockfd);
        void    send_message(std::string message, int client_sockfd);
};
