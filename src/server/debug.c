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

/**
* Debug function who can take va_list in arg
* Print what is send only if DEBUG is define
* If the first character of the format string, this function print the hour
* @param format
* @param ap
*/
void vdebug(char const *format, va_list ap)
{
	#ifdef DEBUG
	struct tm *timet;
	time_t t = time(NULL);

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

/**
* Call vdebug only if status is verified
* @param status
* @param format
* @param ap
*/
void vdebug_if(bool status, char const *format, va_list ap)
{
	if (status) {
		vdebug(format, ap);
	}
}

/**
* Standard debug function
* create a va_list and send it to vdebug
* @param format
* @param ...
*/
void debug(char *format, ...)
{
	#ifdef DEBUG
	va_list ap;

	va_start(ap, format);
	vdebug(format, ap);
	va_end(ap);
	#endif
}

/**
* Create a va_list and send_it to vdebug_if
* @param status
* @param format
* @param ...
*/
void debug_if(bool status, char *format, ...)
{
	#ifdef DEBUG
	va_list ap;

	va_start(ap, format);
	vdebug_if(status, format, ap);
	va_end(ap);
	#endif
}