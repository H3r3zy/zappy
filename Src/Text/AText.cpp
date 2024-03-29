//
// EPITECH PROJECT, 2018
// AText.cpp
// File description:
// AText
//

#include "Text/AText.hpp"

AText::AText(const sf::Font &font, sf::Vector2f &position, uint characterSize) : _position(position)
{
	_text.setFont(font);
	_text.setCharacterSize(characterSize);
}

AText::~AText()
{
}

void AText::setText(const std::string &text)
{
	_text.setString(text);
}

const sf::Text &AText::getText() const
{
	return _text;
}

void AText::setPosition(const sf::Vector2f &position)
{
	_position = position;
	_text.setPosition(_position);
}

const sf::Vector2f &AText::getPosition() const
{
	return _position;
}

AText::AText()
{
}

void AText::setPosition(float x, float y)
{
	_position.x = x;
	_position.y = y;
	_text.setPosition(_position);
}
