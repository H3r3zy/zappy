/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <time.h>
#include "parser.h"
#include "server.h"
#include "debug.h"
#include "parsing.h"

void usage(char *binary)
{
	printf("USAGE: %s -p port -x width -y height -n name1 name2 ... -c "
	"clientsNb -f freq\n", binary);
	printf("       port       is the port number\n");
	printf("       width      is the width of the world\n");
	printf("       height     is the height of the world\n");
	printf("       nameX      is the name of the team X\n");
	printf("       clientsNb  is the number of authorized players per "
	"team\n");
	printf("       freq       is the reciprocal of time unit for execution"
	" of actions\n");
}

argument_t *get_arguments_manager(void) {
	static argument_t manager[] = {
		{"-p", &argument_port, true, false, 0},
		{"-x", &argument_width, true, false, 0},
		{"-y", &argument_height, true, false, 0},
		{"-n", &argument_names, true, false, 0},
		{"-c", &argument_clients_nb, true, false, 0},
		{"-f", &argument_frequency, false, false, 0},
		{NULL, NULL, true, false, 0}
	};

	return manager;
}

int main(int ac, char **av)
{
	server_t serv;
	argument_t *manager = get_arguments_manager();

	int status = 0;

	signal(SIGPIPE, SIG_IGN);
	srand((uint32_t) time(NULL) * getpid());
	memset(&serv, 0, sizeof(server_t));
	serv.freq = 100;
	if (ac < 13) {
		usage(av[0]);
		return 84;
	}
	if (!parser(&serv, manager, av))
		return 84;
	status = server(&serv);
	destroy_server(&serv);
	return status;
}