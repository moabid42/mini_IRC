/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 17:36:01 by moabid            #+#    #+#             */
/*   Updated: 2023/01/21 22:41:56 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "irc.hpp"

class Message
{
    private:
        std::string                 prefix;
        std::string                 command;
        std::vector<std::string>    parameters;
        
    public:
        Message();
        Message(std::string prefix, std::string cmd, std::vector<std::string> params);
        ~Message();

        std::string getPrefix() const;
        std::string getCommand() const;
        std::vector<std::string> getParameters() const;
        std::string getParametersIndex(int index) const;
};
