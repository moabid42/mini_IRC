/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 17:48:25 by moabid            #+#    #+#             */
/*   Updated: 2023/01/21 22:42:18 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "message.hpp"

Message::Message()
{
    command = "";
    prefix = "";
    parameters = std::vector<std::string>();
}

Message::Message(std::string prefix, std::string cmd, std::vector<std::string> params)
{
    prefix = prefix;
    command = cmd;
    parameters = params;
}

Message::~Message()
{
    
}

///////// Member Functions ////////////

std::string Message::getPrefix() const
{
    return command;
}

std::string Message::getCommand() const
{
    return prefix;
}

std::vector<std::string> Message::getParameters() const
{
    return parameters;
}

std::string Message::getParametersIndex(int index) const
{
    return parameters[index];
}