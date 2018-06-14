/*
** EPITECH PROJECT, 2018
** client
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <iostream>
#include "Gui.hpp"

irc::Gui::Gui(int socket, std::vector<int> &listId, bool &displayGui, bool &endClient) : _socketServer(socket), _listId(listId), _displayGui(displayGui), _endClient(endClient)
{
}

int irc::Gui::initDisplayGui()
{
	return 0;
}

void irc::Gui::loopDisplay()
{
	while (1) {
		std::cout << "GUI:" << _displayGui << std::endl;
	}
}