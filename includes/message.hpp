/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 17:36:01 by moabid            #+#    #+#             */
/*   Updated: 2023/01/22 11:53:20 by moabid           ###   ########.fr       */
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

        std::string const &getPrefix() const;
        std::string const &getCommand() const;
        std::vector<std::string> const &getParameters() const;
        std::string const &getParametersIndex(int index) const;
};
