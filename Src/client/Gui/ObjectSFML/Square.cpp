/*
** EPITECH PROJECT, 2018
** PSU_ZAPPY_2017
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <iostream>
#include "Class/Gui/ObjectSFML/Square.hpp"

zap::Square::Square(sf::IntRect pos)
	: AbstractObjectSFML(pos), _object()
{
	this->_object.setPosition(this->_pos.left, this->_pos.top);
	this->_object.setSize(sf::Vector2f(this->_pos.width, this->_pos.height));
	this->_object.setFillColor(sf::Color::White);
}

bool zap::Square::drawObject(sf::RenderWindow &window)
{
	window.draw(this->_object);
	return false;
}

void zap::Square::setColor(sf::Color color)
{
	this->_color = color;
	this->_object.setFillColor(this->_color);
}

void zap::Square::setPos(sf::IntRect pos)
{
	this->_pos = pos;
	this->_object.setPosition(this->_pos.left, this->_pos.top);
	this->_object.setSize(sf::Vector2f(this->_pos.width, this->_pos.height));
}
