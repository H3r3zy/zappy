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
#include <stdbool.h>
#include <sys/time.h>
#include <debug.h>
#include "server.h"
#include "scheduler.h"

static void add_task_in_client(scheduler_t **client_task, char *command, long long int spending_time, void (*function)(struct server_s *server, struct client_s *invoker, char *command))
{
	scheduler_t *task = malloc(sizeof(scheduler_t));
	struct timespec spec;

	if (!task) {
		return;
	}
	clock_gettime(CLOCK_REALTIME, &spec);
	task->spending_time = spending_time;
	task->started_time = spec.tv_sec * STOMS + spec.tv_nsec / NTOMS;
	task->command = command ? strdup(command) : NULL;
	task->function = function;
	*client_task = task;
}

void add_task_to_schedule(client_t *client, long long int spending_time, char *command, void (*function)(struct server_s *server, struct client_s *invoker, char *command))
{
	for (uint i = 0; i < LIMIT_TASK_NUMBER; i++) {
		if (client->task[i] == NULL) {
			add_task_in_client(&(client->task[i]), command, spending_time, function);
			break;
		}
	}
}

static bool check_task(server_t *server, client_t *client, scheduler_t *task)
{
	long long int now_ms = 0;
	struct timespec spec;

	if (!task) {
		return false;
	}
	clock_gettime(CLOCK_REALTIME, &spec);
	now_ms = spec.tv_sec * STOMS + spec.tv_nsec / NTOMS;
	if (task->spending_time <= now_ms - task->started_time) {
		debug("Execute command of %i\n", client->fd);
		if (task->function)
			task->function(server, client, task->command);
		free(task->command);
		free(task);
		return true;
	}
	return false;

}

static void shift_task(client_t *client)
{
	struct timespec spec;

	clock_gettime(CLOCK_REALTIME, &spec);
	for (uint i = 0; i < LIMIT_TASK_NUMBER - 1; i++) {
		client->task[i] = client->task[i + 1];
	}
	if (client->task[0])
		client->task[0]->started_time = spec.tv_sec * STOMS + spec.tv_nsec / NTOMS;
	client->task[LIMIT_TASK_NUMBER - 1] = NULL;
}

void scheduler(server_t *server)
{
	for (client_t *cl = server->clients; cl; cl = cl->next) {
		if (check_task(server, cl, cl->task[0])) {
			cl->task[0] = NULL;
			shift_task(cl);
		}
	}
}