/*
** EPITECH PROJECT, 2018
** Get Next Line
** File description:
** Get Next Line
*/

#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "server.h"

static char *add_str(char **str, char *buff)
{
	size_t len = (str && *str) ? strlen(*str) : 0;
	char *new = malloc(len + strlen(buff) + 1);

	if (!new)
		return (NULL);
	new[0] = 0;
	strcat((!*str || !strlen(*str)) ? new : strcat(new, *str), buff);
	free(*str);
	*str = new;
	return (*str);
}

static ssize_t process_read(int fd, char **save, char *delim)
{
	char buff[READ_SIZE + 1];
	ssize_t len = 0;

	while (!*save || !strstr(*save, delim)) {
		len = read(fd, buff, READ_SIZE);
		if (len < 1 && !*save)
			return (-1);
		else if (len < 1 && *save)
			break;
		buff[len] = 0;
		if (!add_str(save, buff))
			return (-1);
	}
	return (0);
}

static char *cut_save(char **save, char *delim, char *pos)
{
	char *new;
	char *rest = strdup(pos + strlen(delim));

	if (!*save)
		return (NULL);
	if (!rest || !*rest) {
		free(rest);
		rest = NULL;
	}
	*pos = 0;
	new = strdup(*save);
	free(*save);
	*save = rest;
	return (new);
}

char *gnl(int fd, char *delim)
{
	static char *save = NULL;
	char *str = NULL;

	if (process_read(fd, &save, delim) == -1)
		return (NULL);
	if (strstr(save, delim))
		return (cut_save(&save, delim, strstr(save, delim)));
	else {
		str = strdup(save);
		free(save);
		save = NULL;
		return (str);
	}
}
