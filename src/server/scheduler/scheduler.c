/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <server.h>
#include <gui_command.h>
#include "debug.h"
#include "egg.h"
#include "scheduler.h"

/**
* Check if a client as a task and if the time is done execute this task
* @param server
* @param client
* @param task
* @return
*/
static bool check_task(server_t *server, client_t *client, task_t *task,
	ms_t now
)
{
	if (!task)
		return false;
	if (UNITTOMS(task->time_unit, server->freq) <= now - task->started_time) {
		debug("Execute command of %i\n", client->fd);
		if (task->function)
			task->function(server, client, task->command);
		free(task->command);
		free(task);
		return true;
	}
	return false;
}

/**
* Shift task (task[1] become task[0])
* And timer to the new first task start
* @param client
*/
static void shift_task(client_t *client, ms_t now)
{
	for (uint32_t i = 0; i < LIMIT_TASK_NUMBER - 1; i++) {
		client->task[i] = client->task[i + 1];
	}
	if (client->task[0])
		client->task[0]->started_time = now;
	client->task[LIMIT_TASK_NUMBER - 1] = NULL;
}

/**
* Execute first task for a given client when the time is done
* @param server
* @param client
* @param now
*/
static void client_scheduler(server_t *server, client_t *client, ms_t now)
{
	if (check_task(server, client, client->task[0], now)) {
		client->task[0] = NULL;
		shift_task(client, now);
	}
	if (client->team &&
		client->started_time + UNITTOMS(FOOD_UNIT_TIME, server->freq) <
			now) {
		client->started_time = now;
		if (client->user.bag[Food] == 0) {
			die(server, client);
			return;
		}
		client->user.bag[Food]--;
	}
}

/**
* Schedule if a player is in an egg and if time is done break the egg
* @param server
* @param client
* @param now
*/
static void schedule_egg(server_t *server, client_t *client, ms_t now)
{
	egg_t *egg = get_egg_of(client);

	if (now > egg->started_time + UNITTOMS(EGG_UNIT_TIME, server->freq)) {
		debug(GINFO "'%i' hatched (%i,%i:%i)\n", client->fd,
			client->entity->pos.x, client->entity->pos.y,
			client->user.orientation);
		remove_egg(egg);
		gui_eht(server, egg);
		client->status = NORMAL;
	}
}

/**
* For each client in the server, call the client_scheduler
* @param server
*/
void scheduler(server_t *server)
{
	struct timespec spec;
	client_t *client = server->clients;
	client_t *tmp;
	ms_t now;

	clock_gettime(CLOCK_REALTIME, &spec);
	now = spec.tv_sec * STOMS + spec.tv_nsec / NTOMS;
	schedule_resource_generator(server, now);
	while (client) {
		if (client->status == EGG) {
			schedule_egg(server, client, now);
		}
		tmp = client->next;
		client_scheduler(server, client, now);
		client = tmp;
	}
}