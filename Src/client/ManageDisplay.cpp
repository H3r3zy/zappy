/*
** EPITECH PROJECT, 2018
** client
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <unistd.h>
#include "ManageDisplay.hpp"

irc::ManageDisplay::ManageDisplay(int socketServer, const std::string &nick, const std::string &ip) : _socketServer(socketServer), _comm(socketServer, _endClient), _map(_comm, _listId, _displayGui, _endClient), _gui(_comm, nick, ip, _listId, _displayGui, _endClient), _nick(nick)
{
	_threadRead = new my::Thread([&]() {
		_comm.loopRead();
	});

//	_thread = new my::Thread([&]() {
		if (!_gui.initDisplayGui())
			_gui.loopDisplay();
//	});
//	_map.loopDisplay();
}

irc::ManageDisplay::~ManageDisplay()
{
	close(_socketServer);
}