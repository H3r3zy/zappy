/*
** EPITECH PROJECT, 2018
** client
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <unistd.h>
#include "ManageDisplay.hpp"

zap::ManageDisplay::ManageDisplay(int socketServer, const std::string &nick, const std::string &ip, sf::Music &music) : _socketServer(socketServer), _music(music), _comm(socketServer, _endClient),
	_threadRead(new my::Thread([&]() {try {_comm.loopRead();}catch(const std::exception &e){_endClient = true;};})), _map(_comm, _displayGui, _endClient), _gui(_comm, nick, ip, _displayGui, _endClient, _music), _nick(nick)
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
		try {
			_gui.loopDisplay();
		} catch (const std::exception &e) {
			_comm.unlockDisplay();
			_endClient = true;
		};
	});
	if (!_endClient) {
		try {
			_map.loopDisplay();
		} catch (const std::exception &e) {
			_comm.unlockDisplay();
			_endClient = true;
		};

	}
	_threadRead->detach();
	_thread->join();
}

zap::ManageDisplay::~ManageDisplay()
{
	_music.stop();
	close(_socketServer);
}