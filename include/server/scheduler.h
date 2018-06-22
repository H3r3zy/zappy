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
#include "command.h"

#define NTOMS 1000000

#define STOMS 1000

#define UNITTOMS(unit, freq) (long long int) ((unit) / (float) (freq) * 1000)

typedef long long int ms_t;
typedef void (*task_function_t)(server_t *server, client_t *invoker, char *command);

void add_task_to_schedule(client_t *client, uint32_t time_unit, char *command, task_function_t function);
void schedule_resource_generator(server_t *server, ms_t now);
void scheduler(server_t *server);

#endif //PSU_ZAPPY_2017_SCHEDULER_H
