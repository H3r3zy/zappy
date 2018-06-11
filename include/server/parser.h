/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#ifndef PSU_ZAPPY_2017_PARSER_H
#define PSU_ZAPPY_2017_PARSER_H

#include <stdbool.h>
#include "server.h"

typedef struct argument_s {
	char *flag;
	int (*func)(struct argument_s *, void *server, char **av, uint i);
	bool mandatory;
	bool error;
	int call_number;
} argument_t;

bool parser(void *argument, argument_t *manager, char **av);

#endif //PSU_ZAPPY_2017_PARSER_H
