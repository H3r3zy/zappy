/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <iostream>
#include <thread>
#include "SFML_monitor.hpp"
#include "IObjectSFML.hpp"

irc::SFML_monitor::SFML_monitor(const std::string &windowName, std::size_t width,
	std::size_t height) : _windowName(windowName), _windowSize({(float)width, (float)height}),
	_window(sf::VideoMode(width, height), windowName), _scene(0)
{
}

irc::SFML_monitor::~SFML_monitor()
{
	deleteObjects();
}

void irc::SFML_monitor::addObjectToDraw(const std::string &name, irc::IObjectSFML *object, int scene, int layer)
{
	object->setLayer(layer);
	this->_listObject[scene].insert({name, object});
}

void irc::SFML_monitor::closeWindow()
{
	this->_window.close();
}

void irc::SFML_monitor::manageEvent(sf::Event &event)
{
	bool ret = false;
	std::size_t obj_send = 0;
	std::size_t nb_obj = this->_listObject[_scene].size();
	int save = _scene;

	for (int layer = 1000; layer >= 0; layer--) {
		for (auto it = this->_listObject[save].begin(); it != this->_listObject[save].end(); ++it) {
			if (!it->second)
				break;
			if (layer == (int)it->second->getLayer() && it->second->getBoolDisplay()) {
				ret = it->second->updateEvent(event, this->_window, this->_windowSize);
				obj_send++;
			}
			if (this->_listObject[save].size() != nb_obj || _scene != save)
				return;
			if (obj_send == nb_obj || ret)
				break;
		}
	}
	if (event.type == sf::Event::Closed || ret)
		closeWindow();
}

void irc::SFML_monitor::drawObject()
{
	std::size_t obj_draw = 0;

	for (std::size_t layer = 0; layer < 1000 ; ++layer) {
		for (auto it = this->_listObject[_scene].begin(); it != this->_listObject[_scene].end() ; ++it) {
			if (layer == it->second->getLayer() && it->second->getBoolDisplay()) {
				it->second->drawObject(this->_window);
				obj_draw++;
			}
		}
		if (obj_draw == this->_listObject[_scene].size())
			break;
	}
}

void irc::SFML_monitor::callFuncLoop()
{
	int save = _scene;

	for (auto it = this->_listFunc[_scene].begin(); it != this->_listFunc[_scene].end() ; ++it) {
		(*it)();
		if (save != _scene)
			break;
	}
}

void irc::SFML_monitor::loopWindow(irc::Communication *comm)
{
	sf::Event event;

	while (this->_window.isOpen()) {
		if (comm)
			comm->lockDisplay();
		while (this->_window.pollEvent(event))
			this->manageEvent(event);
		this->_window.clear();
		callFuncLoop();
		if (_window.isOpen()) {
			drawObject();
			this->_window.display();
		}
		if (comm) {
			comm->unlockDisplay();
			std::this_thread::sleep_for(std::chrono::milliseconds(2));
		}
	}
}

void irc::SFML_monitor::deleteObjects()
{
	for (auto it = this->_listObject.begin(); it != this->_listObject.end() ; ++it) {
		for (auto idx = it->second.begin(); idx != it->second.end() ; ++idx) {
			delete idx->second;
		}
		it->second.clear();
	}
	this->_listObject.clear();
}

int irc::SFML_monitor::getCurrentScene() const
{
	return this->_scene;
}

void irc::SFML_monitor::setScene(int scene)
{
	this->_scene = scene;
}

sf::Vector2f irc::SFML_monitor::getWindowSize() const
{
	return this->_windowSize;
}

irc::IObjectSFML *irc::SFML_monitor::getObjectByName(std::string name, int scene)
{
	auto result = this->_listObject[scene].find(name);

	if (result == this->_listObject[scene].end())
		return nullptr;
	return result->second;
}

void irc::SFML_monitor::deleteObjectByName(std::string name, int scene)
{
	auto result = this->_listObject[scene].find(name);

	if (result != this->_listObject[scene].end()) {
		delete result->second;
		this->_listObject[scene].erase(result);
	}
}

void irc::SFML_monitor::setNameWindow(std::string name)
{
	_window.setTitle(name);
	_windowName = name;
}

void irc::SFML_monitor::deleteObjectByScene(int scene)
{
	for (auto it = _listObject[scene].begin(); it != _listObject[scene].end() ; ++it) {
		delete it->second;
	}
	_listObject[scene].clear();
}

bool irc::SFML_monitor::isWindowOpen()
{
	return this->_window.isOpen();
}

void irc::SFML_monitor::setPostionWindow(const sf::Vector2i &pos)
{
	_window.setPosition(pos);
}

bool irc::SFML_monitor::isSceneCreated(int scene)
{
	return _listObject.find(scene) != _listObject.end();
}