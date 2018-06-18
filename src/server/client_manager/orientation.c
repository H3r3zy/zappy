/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#include <math.h>
#include "server.h"
#include "debug.h"

/**
 * Fill the delta Arg with the delta between pos1 and pos2
 * @param size
 * @param pos1
 * @param pos2
 * @param delta
 * @return
 */
void fill_delta(pos_t *size, pos_t *pos1, pos_t *pos2, pos_t *delta)
{
	delta->x = pos2->x - pos1->x;
	if (delta->x > size->x / 2) {
		delta->x = pos1->x < pos2->x
			? pos1->x + size->x - pos2->x
			: pos2->x + size->x - pos1->x;
	}
	delta->y = pos2->y - pos1->y;
	if (delta->y > size->y / 2) {
		delta->y = pos1->y < pos2->y
			? pos1->y + size->y - pos2->y
			: pos2->y + size->y - pos1->y;
	}
}

/**
 * Transforme the delta the orientation of other player
 * in orientation from delta
 * @param delta
 * @param orientation
 * @return
 */
int get_o_w_dlt(pos_t *delta, orientation_t orientation)
{
	int o;

	if (delta->x == 0 && delta->y == 0)
		return 0;
	if (delta->x == 0 && delta->y < 0)
		o = 5;
	else if (delta->x == 0)
		o = 1;
	else if (delta->y == 0 && delta->x < 0)
		o = 3;
	else if (delta->y == 0)
		o = 7;
	else if (delta->x > 0 && delta->y > 0)
		o = 6;
	else if (delta->x < 0 && delta->y < 0)
		o = 2;
	else if (delta->x > 0)
		o = 4;
	else
		o = 8;
	o += 8 - (8 - (orientation * 2));
	o = (o - 1) % 8 + 1;
	return o;
}