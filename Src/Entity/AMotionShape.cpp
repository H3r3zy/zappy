//
// Created by wisenoa on 17/06/18.
//


#include "AMotionShape.hpp"

AMotionShape::AMotionShape(sf::Vector2f &position) : _position(position)
{
}

AMotionShape::~AMotionShape()
{
}

void AMotionShape::setPosition(sf::Vector2f &position)
{
	_position = position;
}

void AMotionShape::setPosition(float x, float y)
{
	_position.x = x;
	_position.y = y;
}

const sf::Vector2f &AMotionShape::getPosition() const
{
	return _position;
}

AMotionShape::AMotionShape()
{
}

const uint AMotionShape::getActualSprite() const
{
	return _actualSprite;
}
