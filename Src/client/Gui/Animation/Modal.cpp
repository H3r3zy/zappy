/*
** EPITECH PROJECT, 2018
** PSU_ZAPPY_2017
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <chrono>
#include <iostream>
#include "Modal.hpp"

zap::Modal::Modal(zap::IObjectSFML *object, sf::Vector2i to, std::size_t timeElapsed)
	: AbstractObjectSFML(object->getPos()), _obj(object), _to(to), _timeElapsed(timeElapsed)
{
	this->_alreadyReached = false;
}

zap::Modal::~Modal()
{
	delete this->_obj;
}

bool zap::Modal::updateEvent(sf::Event &event, sf::RenderWindow &window, sf::Vector2f &windowSize)
{
	return this->_obj->updateEvent(event, window, windowSize);
}

void zap::Modal::moveObjectToEnd(void)
{
	sf::IntRect pos = this->_obj->getPos();

	if (pos.left != this->_to.x)
		pos.left += (pos.left < this->_to.x) ? 5 : -5;
	if (pos.top != this->_to.y)
		pos.top += (pos.top < this->_to.y) ? 5 : -5;
	this->_obj->setPos(pos);

	if (pos.left == this->_to.x && pos.top == this->_to.y)
		this->_alreadyReached = true;
}

bool zap::Modal::drawObject(sf::RenderWindow &window)
{
	static auto begin = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

	this->_pos = this->_obj->getPos();
	if (!this->_alreadyReached) {
		auto end = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
		int ms = end - begin;
		if (!this->_timeElapsed || !(ms % this->_timeElapsed)) {
			moveObjectToEnd();
		}
	}
	return this->_obj->drawObject(window);
}

void zap::Modal::setPosObj(sf::IntRect pos)
{
	if (pos != this->_obj->getPos())
		this->_alreadyReached = false;
	this->_obj->setPos(pos);
}

void zap::Modal::setPos(sf::IntRect pos)
{
	this->_alreadyReached = false;
	this->_to = sf::Vector2i(pos.left, pos.top);
}

sf::Vector2i zap::Modal::getToModal() const
{
	return this->_to;
}

sf::IntRect zap::Modal::getPos() const
{
	return this->_obj->getPos();
}

void zap::Modal::setColor(sf::Color color)
{
	this->_obj->setColor(color);
}

bool zap::Modal::getReached() const
{
	return this->_alreadyReached;
}

zap::IObjectSFML *zap::Modal::getObj()
{
	return this->_obj;
}