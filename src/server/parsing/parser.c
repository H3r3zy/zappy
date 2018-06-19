/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#include <string.h>
#include <stdio.h>
#include "parser.h"

static const char *INVALID_ARGUMENT = "Invalid argument '%s' at %i place\n";

static const char *ARGUMENT_REQUIRED = "The argument '%s' is required\n";

static const char *ERROR = "An error appeared with argument '%s'\n";

static bool check_arg(void *argument, argument_t *manager, char **av, uint *i)
{
	for (uint j = 0; manager[j].flag; j++) {
		if (strcmp(manager[j].flag, av[*i]) == 0) {
			*i += manager[j].func(&manager[j], argument, av, *i);
			manager[j].call_number++;
			return true;
		}
	}
	return false;
}

bool parser(void *argument, argument_t *manager, char **av)
{
	bool ret = true;

	for (uint i = 1; av[i]; i++) {
		if (!check_arg(argument, manager, av, &i)) {
			fprintf(stderr, INVALID_ARGUMENT, av[i], i);
			return false;
		}
	}
	for (uint i = 0; manager[i].flag; i++) {
		if (manager[i].mandatory && !manager[i].call_number) {
			fprintf(stderr, ARGUMENT_REQUIRED, manager[i].flag);
			ret = false;
		}
		if (manager[i].error) {
			fprintf(stderr, ERROR, manager[i].flag);
			ret = false;
		}
	}
	return ret;
}