/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 17:48:25 by moabid            #+#    #+#             */
/*   Updated: 2023/01/25 23:36:05 by moabid           ###   ########.fr       */
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
    this->prefix = prefix;
    command = cmd;
    parameters = params;
    std::cout << "The prefix is " << this->prefix << std::endl;
    std::cout << "The cmd is " << cmd << std::endl;
    // std::cout << "the params contains " << params.empty() << std::endl;
    // if (params.empty() == 0)
    //     std::cout << "The parameters is " << parameters[0] << std::endl;
}

Message::~Message()
{
    
}

///////// Member Functions ////////////

std::string  const &Message::getPrefix() const 
{
    return this->prefix;
}

std::string  const &Message::getCommand() const 
{
    return this->command;
}

size_t      const Message::getParamSize()
{
    return parameters.size();
}

std::vector<std::string>  const &Message::getParameters() const 
{
    return parameters;
}

std::string  const Message::getParametersIndex(int index)
{
    return parameters[index];
}