/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#include <memory.h>
#include <time.h>
#include "scheduler.h"

/**
* Add a task given in argument to a task_ptr
* @param client_task
* @param command
* @param spending_time
* @param function
*/
static void add_task_in_client(task_t **client_task, char *command,
	long long int spending_time, task_function_t function)
{
	task_t *task = malloc(sizeof(task_t));
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

/**
* Add a task in a free slot of the client
* @param client
* @param spending_time
* @param command
* @param function
*/
void add_task_to_schedule(client_t *client, ms_t spending_time, char *command,
	task_function_t function)
{
	for (uint i = 0; i < LIMIT_TASK_NUMBER; i++) {
		if (client->task[i] == NULL) {
			add_task_in_client(&client->task[i], command,
				spending_time, function);
			break;
		}
	}
}