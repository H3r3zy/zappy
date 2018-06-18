/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#ifndef PSU_MYIRC_2017_SOCKET_H
#define PSU_MYIRC_2017_SOCKET_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>

typedef int socket_t;

#define SOCKET_ERROR (-1)

#define SIMULATNEOUS_CONNEXION (10)

socket_t i_socket(uint16_t port);
socket_t i_socket_accept(socket_t server);

#endif //PSU_MYIRC_2017_SOCKET_H
