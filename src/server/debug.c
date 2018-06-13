/*
** EPITECH PROJECT, 2018
** Epitech Project
** File description:
** created by sahel.lucas-saoudi@epitech.eu
*/

#include <time.h>
#include <stdarg.h>
#include <stdio.h>
#include "debug.h"

void vdebug(char const *format, va_list ap)
{
	struct tm *timet;
	time_t t = time(NULL);

	#ifdef DEBUG
	timet = localtime(&t);
	if (timet && format[0] == '[') {
		fprintf(stdout, "%02i:%02i:%02i ",
			timet->tm_hour, timet->tm_min, timet->tm_sec);
	}
	vfprintf(stdout, format, ap);
	fflush(stdout);
	#endif
	(void) format;
	(void) ap;
}

void vdebug_if(bool status, char const *format, va_list ap)
{
	if (status) {
		vdebug(format, ap);
	}
}

void debug(char *format, ...)
{
	va_list ap;

	va_start(ap, format);
	vdebug(format, ap);
	va_end(ap);
}

void debug_if(bool status, char *format, ...)
{
	va_list ap;

	va_start(ap, format);
	vdebug_if(status, format, ap);
	va_end(ap);
}