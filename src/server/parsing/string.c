/*
** EPITECH PROJECT, 2018
** String
** File description:
** String
*/

#include <stdlib.h>

size_t char_nb(const char *str, char c)
{
	size_t n = 0;

	for (; *str; ++str)
		if (*str == c)
			++n;
	return n;
}