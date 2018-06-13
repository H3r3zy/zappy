/*
** EPITECH PROJECT, 2018
** client
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <wait.h>
#include <iostream>
#include "Gui.hpp"

irc::Gui::Gui(const pid_t &pid_map) : _pidMap(pid_map)
{
}

void irc::Gui::loopDisplay()
{
	while(1)
		std::cout << "GUI" << std::endl;
}