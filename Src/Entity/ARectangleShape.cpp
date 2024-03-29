//
// Created by wisenoa on 17/06/18.
//


#include "ARectangleShape.hpp"

ARectangleShape::ARectangleShape()
{
}

ARectangleShape::ARectangleShape(sf::Vector2f &position, sf::Vector2f &size) : _position(position), _size(size)
{
	_rectangle.setPosition(_position);
	_rectangle.setSize(_size);
}

ARectangleShape::~ARectangleShape()
{
}

void ARectangleShape::setPosition(sf::Vector2f &position)
{
	_position = position;
}

void ARectangleShape::setPosition(float x, float y)
{
	_position.x = x;
	_position.y = y;
}

const sf::Vector2f &ARectangleShape::getPosition() const
{
	return _position;
}

const sf::RectangleShape &ARectangleShape::getCell() const
{
	return _rectangle;
}