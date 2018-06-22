/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#include <stdint.h>
#include <memory.h>


void write_uint32(char *buffer, int *idx, uint32_t nb)
{
	memcpy(buffer + *idx, &nb, sizeof(uint32_t));
	*idx += sizeof(uint32_t);
}

uint32_t read_uint32(char *buffer, int *idx)
{
	uint32_t nb = 0;

	memcpy(&nb, buffer + *idx, sizeof(uint32_t));
	*idx += sizeof(uint32_t);
	return nb;
}