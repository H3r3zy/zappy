/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <command.h>
#include "command.h"
#include "server.h"
#include "debug.h"
#include "scheduler.h"

static const command_t COMMAND[] = {
	{name: "Forward", function: NULL, verify: NULL, time_unit: 7, argument: false},
	{name: "Right", function: NULL, verify: NULL, time_unit: 7, argument: false},
	{name: "Left", function: NULL, verify: NULL, time_unit: 7, argument: false},
	{name: "Look", function: NULL, verify: NULL, time_unit: 7, argument: false},
	{name: "Inventory", function: &inventory, verify: NULL, time_unit: 1, argument: false},
	{name: "Broadcast", function: NULL, verify: NULL, time_unit: 7, argument: true},
	{name: "Connect_nbr", function: NULL, verify: NULL, time_unit: 0, argument: false},
	{name: "Fork", function: NULL, verify: NULL, time_unit: 42, argument: false},
	{name: "Eject", function: NULL, verify: NULL, time_unit: 7, argument: false},
	{name: "Take", function: NULL, verify: NULL, time_unit: 7, argument: true},
	{name: "Set", function: NULL, verify: NULL, time_unit: 7, argument: true},
	{name: "Incantation", function: NULL, verify: NULL, time_unit: 300, argument: false},
	{name: NULL, function: NULL, verify: NULL, time_unit: 0, argument: false}
};

static void check_command(server_t *server, client_t *client, uint i, char *arg)
{
	if (COMMAND[i].argument && !arg) {
		debug(INFO "%s need argument\n", COMMAND[i].name);
		add_to_queue(client, "ko\n");
		return;
	}
	if (COMMAND[i].verify && !COMMAND[i].verify(server, client, arg)) {
		debug(INFO "don't verify the condition for %s\n", COMMAND[i].name);
		add_to_queue(client, "ko\n");
		return;
	}
	long long int spending_time = COMMAND[i].time_unit / (float) server->freq * 1000;
	debug(INFO "wait for %li ms to exec this command\n", spending_time);
	add_task_to_schedule(client, spending_time, arg, COMMAND[i].function);
}

static void command_manager(server_t *server, client_t *client, char *command)
{
	size_t tmp_len = strlen(command);
	char *name = strtok(command, " \t");
	char *arg = NULL;

	if (!client->team) {
		debug(INFO "'%i' Try to join '%s' team\n", client->fd, command);
		add_to_team(server, client, command);
		return;
	}
	if (tmp_len != strlen(name))
		arg = &command[strlen(name) + 1];
	for (uint i = 0; COMMAND[i].name; i++) {
		if (strcmp(name, COMMAND[i].name) == 0) {
			check_command(server, client, i, arg);
			return;
		}
	}
	add_to_queue(client, "ko\n");
}

void init_client(server_t *server, client_t *client)
{
	srand(time(NULL));
	client->fd = i_socket_accept(server->fd);
	if (client->fd != SOCKET_ERROR) {
		client->user.x = rand() % server->map.size.x;
		client->user.y = rand() % server->map.size.y;
		client->user.level = 1;
		client->user.vision = 1;
		memset(client->queue, 0,
			sizeof(char *) * (LIMIT_TASK_NUMBER + 1));
		client->queue_index = 0;
		client->team = NULL;
		memset(client->user.bag, 0, sizeof(uint) * 7);
		memset(client->task, 0,
			sizeof(scheduler_t *) * LIMIT_TASK_NUMBER);
		debug(INFO "New client on fd %i (pos : %d;%d)\n", client->fd,
			client->user.x, client->user.y);
		server->client_nb++;
		add_to_queue(client, strdup("WELCOME\n"));
	}
	debug_if(client->fd == SOCKET_ERROR, ERROR "Accept error\n");
}

void read_client(server_t *server, client_t *client)
{
	char *request = gnl(client->fd, "\n");

	if (!request)
		disconnect(server, client);
	else {
		debug(INFO "'%i' Client request : %s\n", client->fd, request);
		command_manager(server, client, request);
		free(request);
	}
}

void add_to_queue(client_t *client, char *msg)
{
	if (client->queue_index < LIMIT_TASK_NUMBER)
		client->queue[client->queue_index++] = strdup(msg);
	else
		debug(ERROR "Response queue of client %d is full.\n",
			client->fd);
}

static int try_write(const int fd, char *msg)
{
	size_t len = strlen(msg);
	size_t wrote = 0;
	ssize_t status = 0;

	while (wrote < len) {
		status = write(fd, msg + wrote, len - wrote);
		if (status < 1) {
			debug(ERROR "Failed to wrote response to client %d\n",
			fd);
			return 1;
		}
		wrote += status;
	}
	debug(GINFO "Send to %i => %s", fd, msg);
	return 0;
}

void send_responses(client_t *client)
{
	while (client->queue_index) {
		if (try_write(client->fd, *client->queue) != 0)
			break;
		for (uint i = 1; client->queue[i]; i++)
			client->queue[i - 1] = client->queue[i];
		free(*client->queue);
		client->queue[client->queue_index - 1] = NULL;
		--client->queue_index;
	}
}