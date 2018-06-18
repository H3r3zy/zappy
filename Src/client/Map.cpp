/*
** EPITECH PROJECT, 2018
** client
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <iostream>
#include "Map.hpp"

irc::Map::Map(irc::Communication &comm, std::vector<int> &listId, bool &displayGui, bool &endClient) : _comm(comm), _listId(listId), _displayGui(displayGui), _endClient(endClient)
{
}

void irc::Map::loopDisplay()
{
	while (1) {
		std::cout << "MAP" << std::endl;
	}
}