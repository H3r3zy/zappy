/*
** EPITECH PROJECT, 2018
** client
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <iostream>
#include <thread>
#include "Gui.hpp"

irc::Gui::Gui(irc::Communication &comm, const std::string &nick, const std::string &ip, std::vector<int> &listId, bool &displayGui, bool &endClient) : GuiTexture(), _comm(comm), _listId(listId), _displayGui(displayGui), _endClient(endClient)
{
	_nick = nick;
	_ip = ip;
}

irc::Gui::~Gui()
{
	if (_monitor) {
		if (_monitor->isWindowOpen());
			_monitor->closeWindow();
		delete _monitor;
	}
}

int irc::Gui::initDisplayGui()
{
	_comm.lockDisplay();
	_monitor = new irc::SFML_monitor("Interface User", WIDTH, HEIGHT);
	_monitor->setPostionWindow(sf::Vector2i(1400, 50));
	_monitor->addFuncLoop(0, [this]{
		if (!_displayGui || _endClient)
			_monitor->closeWindow();
	});

	initTexture();
	_comm.unlockDisplay();
	std::this_thread::sleep_for(std::chrono::milliseconds(2));
	return 0;
}

void irc::Gui::loopDisplay()
{
	while (!_endClient) {
		std::cout << "val: " << _displayGui << std::endl;
		if (_displayGui) {
			std::cerr << "INIT" << std::endl;
			initDisplayGui();
			_monitor->loopWindow(&_comm);
			std::cerr << "END" << std::endl;
		}
		_displayGui = false;
	}
	std::cout << "LOOP DISPLAY END" << std::endl;
	if (_monitor->isWindowOpen()); {
		_comm.lockDisplay();
		_monitor->closeWindow();
		_comm.unlockDisplay();
	}

}