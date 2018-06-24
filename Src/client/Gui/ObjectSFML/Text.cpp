/*
** EPITECH PROJECT, 2018
** PSU_ZAPPY_2017
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <iostream>
#include "Class/Gui/ObjectSFML/Text.hpp"

zap::Text::Text(const std::string &pathFont, sf::IntRect pos, const std::string &text)
	: AbstractObjectSFML(pos)
{
	if (this->_font.loadFromFile(pathFont)) {
		this->_text = sf::Text(text, this->_font);
		this->_text.setCharacterSize(this->_pos.height);
		this->_text.setFillColor(sf::Color::White);
		this->_text.setPosition(this->_pos.left, this->_pos.top);
	} else {
		throw std::exception();
	}
}

void zap::Text::setText(const std::string &msg)
{
	this->_msg = msg;
	this->_text.setString(this->_msg);
}

bool zap::Text::drawObject(sf::RenderWindow &window)
{
	window.draw(this->_text);
	return false;
}

std::string zap::Text::getText() const
{
	return this->_text.getString();
}

void zap::Text::setColor(sf::Color color)
{
	this->_text.setFillColor(color);
}

void zap::Text::setPos(sf::IntRect pos)
{
	this->_pos = pos;
	this->_text.setPosition(this->_pos.left, this->_pos.top);
	this->_text.setCharacterSize(this->_pos.height);
}
