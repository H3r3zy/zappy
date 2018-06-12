/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <iostream>
#include "Class/Gui/ObjectSFML/Square.hpp"

irc::Square::Square(sf::IntRect pos)
	: AbstractObjectSFML(pos), _object()
{
	this->_object.setPosition(this->_pos.left, this->_pos.top);
	this->_object.setSize(sf::Vector2f(this->_pos.width, this->_pos.height));
	this->_object.setFillColor(sf::Color::White);
}

bool irc::Square::drawObject(sf::RenderWindow &window)
{
	window.draw(this->_object);
	return false;
}

void irc::Square::setColor(sf::Color color)
{
	this->_color = color;
	this->_object.setFillColor(this->_color);
}

void irc::Square::setPos(sf::IntRect pos)
{
	this->_pos = pos;
	this->_object.setPosition(this->_pos.left, this->_pos.top);
	this->_object.setSize(sf::Vector2f(this->_pos.width, this->_pos.height));
}
