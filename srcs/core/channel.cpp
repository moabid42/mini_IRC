/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 19:18:20 by moabid            #+#    #+#             */
/*   Updated: 2023/01/24 11:08:17 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "channel.hpp"

Channel::Channel()
{ }

Channel::Channel(std::string name) : _name(name)
{ }

Channel::~Channel()
{ }

std::string Channel::getName() const
{
    return _name;
}

std::string Channel::getTopic() const
{
    return _topic;
}

void Channel::setTopic(std::string topic)
{
    _topic = topic;
}

std::map<int, std::string> Channel::getUsers() const
{
    return _users;
}

std::map<std::string, std::string> Channel::getModes() const
{
    return _modes;
}

void Channel::addUser(int socket_fd, std::string username)
{
    _users[socket_fd] = username;
}

void Channel::removeUser(int socket_fd)
{
    _users.erase(socket_fd);
}

void Channel::addMode(std::string mode, std::string param)
{
    _modes[mode] = param;
}

void Channel::removeMode(std::string mode) 
{
    _modes.erase(mode);
}

void Channel::broadcastMessage(std::string message)
{
    // Send the message to the user's socket descriptor
    // You can use the send_message in SocketServer
}
