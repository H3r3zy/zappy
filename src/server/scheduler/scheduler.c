/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#include <stdlib.h>
#include <server.h>
#include <time.h>
#include <string.h>
#include "server.h"

static void add_task_in_client(scheduler_t **client_task, char *command, long long int resting_time, void (*function)(struct server_s *server, struct client_s *invoker, char *command))
{
	scheduler_t *task = malloc(sizeof(scheduler_t));

	if (!task)
		return;
	task->resting_time = resting_time;
	task->started_time = time(NULL);
	task->command = strdup(command);
	*client_task = task;
}

void add_task_to_schedule(client_t *client, long long int resting_time, char *command, void (*function)(struct server_s *server, struct client_s *invoker, char *command))
{
	for (uint i = 0; i < LIMIT_TASK_NUMBER; i++) {
		if (client->task[i] == NULL) {
			add_task_in_client(&(client->task[i]), command, resting_time, function);
		}
	}
}

static void check_task(server_t *server, client_t *client, scheduler_t **task)
{
	long long int now = time(NULL);

	if (!(*task))
		return;
	(*task)->resting_time -= now - (*task)->started_time;
	if ((*task)->resting_time <= 0) {
		(*task)->function(server, client, (*task)->command);
		free((*task)->command);
		free(*task);
		*task = NULL;
	}

}

void scheduler(server_t *server)
{
	for (client_t *cl = server->clients; cl; cl = cl->next) {
		for (uint i = 0; i < LIMIT_TASK_NUMBER; i++) {
			check_task(server, cl, &(cl->task[i]));
		}
	}
}