/*
** EPITECH PROJECT, 2018
** client
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <iostream>
#include "Gui.hpp"

irc::Gui::Gui(irc::Communication &comm, const std::string &nick, const std::string &ip, std::vector<int> &listId, bool &displayGui, bool &endClient) : GuiTexture(), _comm(comm), _listId(listId), _displayGui(displayGui), _endClient(endClient)
{
	_nick = nick;
	_ip = ip;
}

irc::Gui::~Gui()
{
	if (_monitor) {
		_monitor->closeWindow();
		delete _monitor;
	}
}

int irc::Gui::initDisplayGui()
{
	_monitor = new irc::SFML_monitor("Interface User", WIDTH, HEIGHT);
	_monitor->addFuncLoop(0, [this]{
		if (!_displayGui) {
			_currentlyGuiDisplay = false;
			_monitor->closeWindow();
			_monitor = nullptr;
		}
	});

	initTexture();
	return 0;
}

void irc::Gui::loopDisplay()
{
	while (!_endClient /* TODO: delete the second condition */ && _monitor->isWindowOpen()) {
		std::cout << "val: " << _displayGui << ", " << _currentlyGuiDisplay << std::endl;
		if (_displayGui && !_currentlyGuiDisplay) {
			if (!_monitor && initDisplayGui())
				break;
			_currentlyGuiDisplay = true;
		}
		if (_monitor)
			_monitor->loopWindow();
	}
}