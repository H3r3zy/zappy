/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#ifndef PSU_ZAPPY_2017_SCHEDULER_H
#define PSU_ZAPPY_2017_SCHEDULER_H

#include <stdlib.h>
#include "server.h"

void add_task_to_schedule(client_t *client, long long int resting_time, char *command, void (*function)(struct server_s *server, struct client_s *invoker, char *command));
void scheduler(server_t *server);

#endif //PSU_ZAPPY_2017_SCHEDULER_H
