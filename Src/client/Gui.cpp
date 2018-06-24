/*
** EPITECH PROJECT, 2018
** client
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <iostream>
#include <thread>
#include "Gui.hpp"

irc::Gui::Gui(irc::Communication &comm, const std::string &nick,
	const std::string &ip, bool &displayGui, bool &endClient, sf::Music &music
) : GuiTexture(*this), shackTexture(*this), IATexture(*this), _comm(comm), _music(music),
	_displayGui(displayGui), _endClient(endClient)
{
	_nick = nick;
	_ip = ip;
}

irc::Gui::~Gui()
{
	if (_monitor) {
		if (_monitor->isWindowOpen())
			_monitor->closeWindow();
		delete _monitor;
	}
}

void irc::Gui::addGenericFunction(int scene)
{
	_monitor->addFuncLoop(scene, [this] {
		if (!_comm._listId.empty() && !_monitor->getCurrentScene()) {
			if (_comm._listId[0] != -1)
				_monitor->setScene(1);
			else
				_monitor->setScene(-1);
		}
	});
	_monitor->addFuncLoop(scene, [this] {
		if (!_displayGui || _endClient)
			_monitor->closeWindow();
	});
}

int irc::Gui::initDisplayGui()
{
	_comm.lockDisplay();
	_monitor = new irc::SFML_monitor("Interface User", WIDTH, HEIGHT);
	_monitor->setPostionWindow(sf::Vector2i(1400, 50));

	addGenericFunction(0);
	addGenericFunction(-1);
	addGenericFunction(1);

	irc::GuiTexture::initTexture();
	irc::shackTexture::initTexture();
	irc::IATexture::initTexture();
	_comm.unlockDisplay();
	std::this_thread::sleep_for(std::chrono::milliseconds(2));
	return 0;
}

void irc::Gui::loopDisplay()
{
	while (!_endClient) {
		if (_displayGui) {
			initDisplayGui();
			_monitor->loopWindow(&_comm);
			_displayGui = false;
		}
		_comm._listId.clear();
	}
	if (_monitor->isWindowOpen()) {
		_comm.lockDisplay();
		_monitor->closeWindow();
		_comm.unlockDisplay();
	}
}