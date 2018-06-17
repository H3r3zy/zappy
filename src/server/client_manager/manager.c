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
#include <server.h>
#include "command.h"
#include "server.h"
#include "debug.h"
#include "scheduler.h"

static const command_t COMMAND[] = {
	{name: "Forward", function: &forward_cmd, verify: NULL, time_unit: 7, argument: false},
	{name: "Right", function: &right_cmd, verify: NULL, time_unit: 7, argument: false},
	{name: "Left", function: &left_cmd, verify: NULL, time_unit: 7, argument: false},
	{name: "Look", function: &look_cmd, verify: NULL, time_unit: 7, argument: false},
	{name: "Inventory", function: &inventory_cmd, verify: NULL, time_unit: 1, argument: false},
	{name: "Broadcast", function: &broadcast_cmd, verify: NULL, time_unit: 7, argument: true},
	{name: "Connect_nbr", function: &connect_nbr_cmd, verify: NULL, time_unit: 0, argument: false},
	{name: "Fork", function: &fork_cmd, verify: NULL, time_unit: 42, argument: false},
	{name: "Eject", function: &eject_cmd, verify: NULL, time_unit: 7, argument: false},
	{name: "Take", function: &take_cmd, verify: NULL, time_unit: 7, argument: true},
	{name: "Set", function: &set_cmd, verify: NULL, time_unit: 7, argument: true},
	{name: "Incantation", function: &incantation_cmd, verify: &incantation_verify, time_unit: 300, argument: false},
#ifdef DEBUG
	{name: "Pos", function: &pos, verify: NULL, time_unit: 1, argument: false},
	{name: "Setpos", function: &setpos_cmd, verify: NULL, time_unit: 1, argument: false},
#endif
	{name: NULL, function: NULL, verify: NULL, time_unit: 0, argument: false}
};

static void check_command(server_t *server, client_t *client, uint i, char *arg)
{
	if (client->status == EGG) {
		debug(INFO "'%i' is an EGG, can't do action\n", client->fd);
		add_to_queue(client, "ko\n");
		return;
	}
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
	add_task_to_schedule(client, COMMAND[i].time_unit, arg, COMMAND[i].function);
}

static void command_manager(server_t *server, client_t *client, char *command)
{
	size_t tmp_len = strlen(command);
	char *name = strtok(command, " \t");
	char *arg = NULL;

	if (!name)
		return;
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

int read_client(server_t *server, client_t *client)
{
	char *request = gnl(client->fd, "\n");

	if (!request)
		return 1;
	debug(INFO "'%i' Client request : %s\n", client->fd, request);
	command_manager(server, client, request);
	free(request);
	return 0;
}