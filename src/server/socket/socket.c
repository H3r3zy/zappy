/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#include <stdio.h>
#include "debug.h"
#include "socket.h"

static socket_t i_socket_listen(socket_t fd)
{
	if (listen(fd, SIMULATNEOUS_CONNEXION) == SOCKET_ERROR) {
		close(fd);
		debug(ERROR "listen error\n");
		return SOCKET_ERROR;
	}
	return fd;
}

static socket_t i_socket_bind(socket_t fd, uint16_t port)
{
	struct sockaddr_in sin = {0};

	sin.sin_port = htons(port);
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(fd, (struct sockaddr *) &sin, sizeof(sin)) == SOCKET_ERROR) {
		debug(ERROR "bind error\n");
		close(fd);
		return SOCKET_ERROR;
	}
	return fd;
}

socket_t i_socket(uint16_t port)
{
	socket_t fd = socket(AF_INET, SOCK_STREAM, 0);
	int optval = 1;

	if (fd == SOCKET_ERROR) {
		debug(ERROR "socket error\n");
		return SOCKET_ERROR;
	}
	setsockopt(fd, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval));
	if (i_socket_bind(fd, port) == SOCKET_ERROR) {
		return SOCKET_ERROR;
	}
	return i_socket_listen(fd);
}

socket_t i_socket_accept(socket_t server)
{
	struct sockaddr_in sin = {0};
	socklen_t sinsize = sizeof(sin);
	int fd = accept(server, (struct sockaddr *) &sin, &sinsize);

	debug_if(fd == SOCKET_ERROR, ERROR "accept error\n");
	return fd;
}