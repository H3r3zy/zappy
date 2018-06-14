/*
** EPITECH PROJECT, 2018
** client
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <unistd.h>
#include "ManageDisplay.hpp"

irc::ManageDisplay::ManageDisplay(int socketServerMap, int socketServerGui) : _socketServerMap(socketServerMap), _socketServerGui(socketServerGui), _map(socketServerMap, _listId, _displayGui, _endClient), _gui(socketServerGui, _listId, _displayGui, _endClient)
{
	_thread = new my::Thread([&]() {
		if (!_gui.initDisplayGui())
			_gui.loopDisplay();
	});
	_displayGui = false;
	_map.loopDisplay();
}

irc::ManageDisplay::~ManageDisplay()
{
	close(_socketServerGui);
	close(_socketServerMap);
}