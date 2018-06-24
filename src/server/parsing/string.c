/*
** EPITECH PROJECT, 2018
** String
** File description:
** String
*/

#include <stdlib.h>
#include <string.h>
#include <debug.h>
#include "server.h"
#include "command.h"

size_t char_nb(const char *str, char c)
{
	size_t n = 0;

	for (; *str; ++str)
		if (*str == c)
			++n;
	return n;
}


/**
* @param str
* @param toadd
* @param len
* @param opt
* @return str
*/
void concat(char *toadd, size_t len, look_opt_t *opt)
{
	size_t len_after = *opt->len + len;
	while (len_after >= *opt->size) {
		*opt->size += LOOK_STR_SIZE;
		*opt->str = realloc(*opt->str, *opt->size);
		if (!*opt->str)
			return;
	}
	strcpy(*opt->str + *opt->len, toadd);
	*opt->len = len_after;
}