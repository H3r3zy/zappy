/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <iostream>
#include "Container.hpp"

irc::Container::Container(sf::IntRect pos) : AbstractObjectSFML(pos)
{
}

irc::Container::~Container()
{
	for (auto it = _listObject.begin(); it != _listObject.end() ; ++it) {
		delete it->second;
	}
	_listObject.clear();
}

void irc::Container::setLayer(std::size_t layer)
{
	for (auto it = this->_listObject.begin(); it != this->_listObject.end() ; ++it) {
		it->second->setLayer(it->second->getLayer() - _layer + layer);
	}
	_layer = layer;
}

void irc::Container::addObjectList(std::string name, irc::IObjectSFML *obj, int layer)
{
	sf::IntRect tmp = obj->getPos();
	tmp.top += this->_pos.top;
	tmp.left += this->_pos.left;
	obj->setPos(tmp);
	obj->setLayer(obj->getLayer() + _layer + layer);

	this->_listObject.insert({name, obj});
}

bool irc::Container::drawObject(sf::RenderWindow &window)
{
	int obj_draw = 0;

	for (std::size_t layer = 0; layer < 1000 ; ++layer) {
		for (auto it = this->_listObject.begin(); it != this->_listObject.end() ; ++it) {
			if (layer == it->second->getLayer() && it->second->getBoolDisplay()) {
				it->second->drawObject(window);
				obj_draw++;
			}
		}
		if ((unsigned int)obj_draw == this->_listObject.size())
			break;
	}
	return false;
}

bool irc::Container::updateEvent(sf::Event &event, sf::RenderWindow &window, sf::Vector2f &windowSize)
{
	std::size_t obj_send = 0;
	std::size_t nb_obj = this->_listObject.size();
	_break = false;

	if (!this->_isUsed)
		return false;
	manageScroll(event);
	managePosMouse(event, window, windowSize);
	manageKeyBinding(event);
	for (int layer = 1000; layer >= 0 && !_break; --layer) {
		for (auto it = this->_listObject.begin(); it != this->_listObject.end() && !_break; ++it) {
			if ((std::size_t)layer == it->second->getLayer() && it->second->getBoolDisplay()) {
				it->second->updateEvent(event, window, windowSize);
				obj_send++;
			}
			if (this->_listObject.size() != nb_obj)
				return false;
			if (obj_send == nb_obj)
				break;
		}
	}
	return false;
}

irc::IObjectSFML *irc::Container::getObjectByName(std::string name)
{
	auto result = this->_listObject.find(name);

	if (result == this->_listObject.end())
		return nullptr;
	return result->second;
}

void irc::Container::setColor(sf::Color color __attribute__((unused)))
{
}

void irc::Container::setPos(sf::IntRect pos)
{
	sf::IntRect tmp;

	for (auto it = this->_listObject.begin(); it != this->_listObject.end() ; ++it) {
		tmp = it->second->getPos();
		tmp.top += pos.top - this->_pos.top;
		tmp.left += pos.left - this->_pos.left;
		it->second->setPos(tmp);
	}
	this->_pos = pos;
}

void irc::Container::breakEvent()
{
	_break = true;
}