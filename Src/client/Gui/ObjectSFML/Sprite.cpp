/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <iostream>
#include "Class/Gui/ObjectSFML/Sprite.hpp"

irc::Sprite::Sprite(const std::string &filePath, sf::IntRect pos, const sf::IntRect &rect) : AbstractObjectSFML(pos), _object()
{
	if (this->_texture.loadFromFile(filePath)) {
		this->_object.setTexture(this->_texture);
		if (rect != sf::IntRect(0, 0, 0, 0))
			this->_object.setTextureRect(rect);

		sf::FloatRect size = this->_object.getGlobalBounds();
		this->_object.setScale(sf::Vector2f(this->_pos.width / size.width, this->_pos.height / size.height));
		this->_object.setPosition(this->_pos.left, this->_pos.top);
	} else {
		throw std::exception();
	}
}

bool irc::Sprite::drawObject(sf::RenderWindow &window)
{
	this->_object.setPosition(this->_pos.left, this->_pos.top);
	this->_object.setTexture(this->_texture);

	window.draw(this->_object);
	return false;
}

void irc::Sprite::setColor(sf::Color color __attribute__((unused)))
{
}

void irc::Sprite::setPos(sf::IntRect pos)
{
	bool check = false;

	if (pos.height == this->_pos.height && pos.width == this->_pos.width)
		check = true;

	this->_pos = pos;
	sf::FloatRect size = this->_object.getLocalBounds();
	if (!check)
		this->_object.setScale(sf::Vector2f(this->_pos.width / size.width, this->_pos.height / size.height));

	this->_object.setPosition(this->_pos.left, this->_pos.top);
}

void irc::Sprite::setMirror(sf::Vector2f val)
{
	sf::FloatRect size = this->_object.getLocalBounds();

	this->_object.setOrigin(size.width / 2, size.height / 2);
	this->_object.setScale(val);
	if (val.y == -1.f) {
		this->_object.setScale(sf::Vector2f(this->_pos.width / size.width, -(this->_pos.height / size.height)));
		this->_object.setOrigin(0, size.height);
	}
	if (val.x == -1.f) {
		this->_object.setScale(sf::Vector2f(-(this->_pos.width / size.width), this->_pos.height / size.height));
		this->_object.setOrigin(size.width, 0);
	}
	this->setPos(_pos);
}