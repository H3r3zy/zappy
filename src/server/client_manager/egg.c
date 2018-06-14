/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#include <stdlib.h>
#include "server.h"

/**
* Get the egg of the client (client)
* @param client
* @return
*/
egg_t *get_egg_of(client_t *client)
{
	for (egg_t *egg = client->team->eggs; egg; egg = egg->next) {
		if (egg->client == client) {
			return egg;
		}
	}
	return NULL;
}

/**
* remove the egg in argument and free him
* @param egg
*/
void remove_egg(egg_t *egg)
{
	if (egg->prev)
		egg->prev->next = egg->next;
	if (egg->next)
		egg->next->prev = egg->prev;
	if (egg->team->eggs == egg)
		egg->team->eggs = NULL;
	free(egg);
}
