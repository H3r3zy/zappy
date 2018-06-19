/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parser.h"
#include "server.h"

int argument_port(struct argument_s *manager, void *server, char **av, uint32_t i)
{
	if (!av[i + 1]) {
		manager->error = true;
		return 0;
	}
	((server_t *) server)->port = (ushort) atoi(av[i + 1]);
	return 1;
}

int argument_width(struct argument_s *manager, void *server, char **av, uint32_t i)
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

int argument_height(struct argument_s *manager, void *server, char **av, uint32_t i)
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


int argument_clients_nb(struct argument_s *manager, void *server, char **av, uint32_t i)
{
	if (!av[i + 1]) {
		manager->error = true;
		return 0;
	}
	((server_t *) server)->max_clients_per_teams = (uint32_t) atoi(av[i + 1]);
	if (((server_t *) server)->max_clients_per_teams == 0) {
		manager->error = true;
	}
	return 1;
}

int argument_frequency(struct argument_s *manager, void *server, char **av, uint32_t i)
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

int argument_names(struct argument_s *manager, void *server, char **av, uint32_t i)
{
	int j = i + 1;

	if (!av[i + 1]) {
		manager->error = true;
		return 0;
	}
	while (av[j] && av[j][0] != '-') {
		if (!strcmp(av[j], "gui")) {
			manager->error = true;
			return 0;
		}
		add_teams(server, av[j]);
		j++;
	}
	if (j - i == 1) {
		manager->error = true;
		return 0;
	}
	return j - i - 1;
}