/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** read.c
*/

#include <stdlib.h>
#include <string.h>
#include "server.h"

int pollin_client(server_t *server, client_t *client)
{
	int status = read_client(client);
	char *cmdend;
	char *cmd;
	size_t off = 0;

	if (status != 0)
		return 1;
	cmd = client->buff;
	cmdend = strchr(cmd, '\n');
	while (cmdend) {
		*cmdend = 0;
		command_manager(server, client, cmd);
		off += cmdend - cmd + 1;
		cmd = cmdend + 1;
		cmdend = strchr(cmd, '\n');
	}
	*client->buff = 0;
	if (client->buff[off]) {
		memmove(client->buff, client->buff + off,
			client->buff_len - off + 1);
		client->buff_len -= off;
	}
	return 0;
}

int read_client(client_t *client)
{
	char buff[READ_SIZE + 1];
	ssize_t status = read(client->fd, buff, READ_SIZE);

	if (status < 1)
		return 1;
	buff[status] = 0;
	if (client->buff_len + status >= READ_SIZE) {
		client->buff_size += READ_SIZE;
		client->buff = realloc(client->buff, client->buff_size + 1);
	}
	strcat(client->buff, buff);
	client->buff_len += status;
	return 0;
}