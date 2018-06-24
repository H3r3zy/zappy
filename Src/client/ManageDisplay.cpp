/*
** EPITECH PROJECT, 2018
** client
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <unistd.h>
#include "ManageDisplay.hpp"

irc::ManageDisplay::ManageDisplay(int socketServer, const std::string &nick, const std::string &ip, sf::Music &music) : _socketServer(socketServer), _music(music), _comm(socketServer, _endClient),
	_threadRead(new my::Thread([&]() {_comm.loopRead();})), _map(_comm, _displayGui, _endClient), _gui(_comm, nick, ip, _displayGui, _endClient, _music), _nick(nick)
{
	bool check = true;

	if (music.getStatus() == sf::SoundSource::Paused)
		check = false;
	music.stop();
	if (!_music.openFromFile("extra/gui/map.ogg"))
		throw std::exception();
	_music.setLoop(true);
	if (check)
		_music.play();

	_thread = new my::Thread([&]() {
		_gui.loopDisplay();
	});
	_map.loopDisplay();
	_threadRead->detach();
	_thread->join();
}

irc::ManageDisplay::~ManageDisplay()
{
	_music.stop();
	close(_socketServer);
}