/*
** EPITECH PROJECT, 2018
** client
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <unistd.h>
#include "ManageDisplay.hpp"

irc::ManageDisplay::ManageDisplay(int socketServer, const std::string &nick, const std::string &ip) : _socketServer(socketServer), _comm(socketServer, _endClient), _thread(new my::Thread([&]() {
	std::cout << "tamere" << std::endl;
	_comm.loopRead();
})), _map(_comm, _displayGui, _endClient), _gui(_comm, nick, ip, _displayGui, _endClient), _nick(nick)
{
	_thread = new my::Thread([&]() {
		_gui.loopDisplay();
	});
	_map.loopDisplay();
	_thread->join();
}

irc::ManageDisplay::~ManageDisplay()
{
	close(_socketServer);
}