/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 15:41:32 by moabid            #+#    #+#             */
/*   Updated: 2023/01/22 23:50:33 by moabid           ###   ########.fr       */
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
#include <sys/select.h>
#include <poll.h>
#include <fcntl.h>

#include <vector>
#include <map>
#include <map>

#define D_PORT 6667 //default port
#define MAX_CLIENTS 1024
#define BUFSIZE 256

void    err_and_ext(const char *mssg);