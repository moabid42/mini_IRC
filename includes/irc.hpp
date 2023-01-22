/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 15:41:32 by moabid            #+#    #+#             */
/*   Updated: 2023/01/22 10:36:12 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <cstdbool>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <vector>
#include <map>
#include <unordered_map>

#define D_PORT 6667 //default port

void    err_and_ext(const char *mssg);