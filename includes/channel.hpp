/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 19:05:09 by moabid            #+#    #+#             */
/*   Updated: 2023/01/25 15:43:13 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "irc.hpp"

class SocketServer;

class Channel
{
    private:
        std::string                                     _name;
        std::string                                     _topic;
        std::map<int, std::string>                      _users; // socket descriptor as key and username as value
        std::map<std::string, std::string>              _modes; // mode as key and parameter as value
    
    public:
        Channel();
        Channel(std::string name);
        ~Channel();
    
        std::string getName() const;
        std::string getTopic() const;
        void setTopic(std::string topic);
        std::map<int, std::string> getUsers() const;
        std::map<std::string, std::string> getModes() const;
    
        void addUser(int socket_fd, std::string username);
        void removeUser(int socket_fd);
        void addMode(std::string mode, std::string param);
        void removeMode(std::string mode);
        void broadcastMessage(std::string message);
        void printUsers() const;
};