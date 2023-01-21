/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 15:48:05 by moabid            #+#    #+#             */
/*   Updated: 2023/01/21 20:48:22 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"
#include "socket_srv.hpp"

bool    input_validator(int argc, char **argv)
{
    if (argc != 3)
        err_and_ext("Invalid Input: ./ircserv <port> <password>");
    for (int i = 0; i < strlen(argv[1]); i++)
        if (!isdigit(argv[1][i]))
            return (false);
    return (true);
}

void    sockerserv_create(int port, char *pass)
{
    std::string     password(pass);
    SocketServer    server(port, password);
    int             client_sockfd;
    
    client_sockfd = server.accept_connection();
    server.read_write_loop(client_sockfd);
}

int main(int argc, char **argv)
{
    if (input_validator(argc, argv) == true)
    {
        sockerserv_create(std::atoi(argv[1]), argv[2]);
        return (true);
    }
    return (false);
}