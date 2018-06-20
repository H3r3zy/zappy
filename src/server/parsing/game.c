/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** game.c
*/

#include "server.h"
#include "parser.h"

int argument_width(struct argument_s *manager, void *server,
	char **av, uint32_t i)
{
	if (!av[i + 1]) {
		manager->error = true;
		return 0;
	}
	((server_t *) server)->map.size.x = (uint32_t) atoi(av[i + 1]);
	if (((server_t *) server)->map.size.x == 0) {
		manager->error = true;
	}
	return 1;
}

int argument_height(struct argument_s *manager, void *server,
	char **av, uint32_t i)
{
	if (!av[i + 1]) {
		manager->error = true;
		return 0;
	}
	((server_t *) server)->map.size.y = (uint32_t) atoi(av[i + 1]);
	if (((server_t *) server)->map.size.y == 0) {
		manager->error = true;
	}
	return 1;
}

int argument_frequency(struct argument_s *manager, void *server,
	char **av, uint32_t i)
{
	if (!av[i + 1]) {
		manager->error = true;
		return 0;
	}
	((server_t *) server)->freq = (uint32_t) atoi(av[i + 1]);
	if (((server_t *) server)->freq == 0) {
		manager->error = true;
	}
	return 1;
}