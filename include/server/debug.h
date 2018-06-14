/*
** EPITECH PROJECT, 2018
** Epitech Project
** File description:
** created by sahel.lucas-saoudi@epitech.eu
*/

#ifndef DEBUG_H
# define DEBUG_H

#include <stdbool.h>
#include <stdarg.h>

#define RESET "\033[0m"
#define BLACK "\033[30m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define PINK "\033[35m"
#define CYAN "\033[36m"
#define GREY "\033[37m"

#define CLR(color, str) color str RESET

#define ERROR 	  "[" RED    "ERROR"   RESET "] "
#define WARNING   "[" YELLOW "WARNING" RESET "] "
#define INFO      "[" CYAN   "Info"    RESET "] "
#define GINFO 	  "[" GREEN  "Info"    RESET "] "

void debug(char *format, ...);
void debug_if(bool, char *format, ...);

void vdebug(char const *format, va_list ap);
void vdebug_if(bool, char const *format, va_list ap);

#endif /* !DEBUG_H */
