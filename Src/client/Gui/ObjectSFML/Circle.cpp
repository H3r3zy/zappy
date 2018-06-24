/*
** EPITECH PROJECT, 2018
** PSU_ZAPPY_2017
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <iostream>
#include "Class/Gui/ObjectSFML/Circle.hpp"

zap::Circle::Circle(sf::IntRect pos, std::size_t sides)
	: AbstractObjectSFML(pos), _object(pos.width, sides)
{
	this->_object.setPosition(this->_pos.left, this->_pos.top);
	this->_object.setFillColor(sf::Color::White);
}

void zap::Circle::rotate(int val)
{
	this->_object.rotate(val);
}

bool zap::Circle::drawObject(sf::RenderWindow &window)
{
	window.draw(this->_object);
	return false;
}

void zap::Circle::setColor(sf::Color color)
{
	this->_color = color;
	this->_object.setFillColor(this->_color);
}

void zap::Circle::setPos(sf::IntRect pos)
{
	this->_pos = pos;
	this->_object.setPosition(this->_pos.left, this->_pos.top);
	this->_object.setRadius(this->_pos.width);
}
