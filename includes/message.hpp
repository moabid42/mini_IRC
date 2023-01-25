/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 17:36:01 by moabid            #+#    #+#             */
/*   Updated: 2023/01/25 15:31:19 by moabid           ###   ########.fr       */
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
        size_t      const getParamSize();
        std::vector<std::string> const &getParameters() const;
        std::string const getParametersIndex(int index);
};
