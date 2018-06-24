/*
** EPITECH PROJECT, 2018
** client
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <iostream>
#include <thread>
#include "Gui.hpp"

zap::Gui::Gui(zap::Communication &comm, const std::string &nick,
	const std::string &ip, bool &displayGui, bool &endClient, sf::Music &music
) : GuiTexture(*this), shackTexture(*this), IATexture(*this), _comm(comm), _music(music),
	_displayGui(displayGui), _endClient(endClient)
{
	_nick = nick;
	_ip = ip;
}

zap::Gui::~Gui()
{
	if (_monitor) {
		if (_monitor->isWindowOpen())
			_monitor->closeWindow();
		delete _monitor;
	}
}

void zap::Gui::addGenericFunction(int scene)
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

int zap::Gui::initDisplayGui()
{
	_comm.lockDisplay();
	_monitor = new zap::SFML_monitor("Interface User", WIDTH, HEIGHT);
	_monitor->setPostionWindow(sf::Vector2i(1400, 50));

	addGenericFunction(0);
	addGenericFunction(-1);
	addGenericFunction(1);

	zap::GuiTexture::initTexture();
	zap::shackTexture::initTexture();
	zap::IATexture::initTexture();
	_comm.unlockDisplay();
	std::this_thread::sleep_for(std::chrono::milliseconds(2));
	return 0;
}

void zap::Gui::loopDisplay()
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