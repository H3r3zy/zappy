/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#ifndef PSU_ZAPPY_2017_PARSING_H
#define PSU_ZAPPY_2017_PARSING_H

#include <stdlib.h>

int argument_port(struct argument_s *, void *, char **av, uint32_t i);
int argument_width(struct argument_s *, void *, char **av, uint32_t i);
int argument_height(struct argument_s *, void *, char **av, uint32_t i);
int argument_clients_nb(struct argument_s *, void *, char **av, uint32_t i);
int argument_frequency(struct argument_s *, void *, char **av, uint32_t i);
int argument_names(struct argument_s *, void *, char **av, uint32_t i);

#endif //PSU_ZAPPY_2017_PARSING_H
