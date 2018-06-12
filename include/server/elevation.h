/*
** EPITECH PROJECT, 2018
** Elevation Headet File
** File description:
** Elevation Headet File
*/

#ifndef ELEVATION_H_
#define ELEVATION_H_

typedef struct elevation_s
{
        char players;
        char linemate;
        char deraumere;
        char sibur;
        char mendiane;
        char phiras;
	char thystame;
} elevation_t;

extern elevation_t elevations[];

/*
elevation_t elevations[] = {
	{1, 1, 0, 0, 0, 0, 0},
	{2, 1, 1, 1, 0, 0, 0},
	{2, 2, 0, 1, 0, 2, 0},
	{4, 1, 1, 2, 0, 1, 0},
	{4, 1, 2, 1, 3, 0, 0},
	{6, 1, 2, 3, 0, 1, 0},
	{6, 2, 2, 2, 2, 2, 1}
};
if (elevations[player_lvl - 1].players == ... &&
 	elevations[lvl - 1].linemate == ...)
 	lvlup();
*/

#endif /* ! ELEVATION_H_ */