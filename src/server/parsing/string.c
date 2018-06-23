/*
** EPITECH PROJECT, 2018
** String
** File description:
** String
*/

#include <stdlib.h>
#include <string.h>

size_t char_nb(const char *str, char c)
{
	size_t n = 0;

	for (; *str; ++str)
		if (*str == c)
			++n;
	return n;
}

char *concat(char *s1, char *s2)
{
	char *str;

	if (!s1)
		return s2;
	if (!s2)
		return s1;
	str = realloc(s1, strlen(s1) + strlen(s2) + 1);
	if (!str)
		return s1;
	str = strcat(str, s2);
	return str;
}