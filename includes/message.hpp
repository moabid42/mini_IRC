/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 17:36:01 by moabid            #+#    #+#             */
/*   Updated: 2023/01/21 17:52:02 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "irc.hpp"

class Message
{
    public:
        std::string                 prefix;
        std::string                 command;
        std::vector<std::string>    parameters;
        
        Message();
        ~Message();
};
