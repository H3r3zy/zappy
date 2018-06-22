//
// Created by wisenoa on 17/06/18.
//

#include <iostream>
#include "Text/GameText.hpp"

GameText::GameText(const sf::Font &font, sf::Vector2f &position) : AText(font, position, 12)
{
	_text.setFillColor(sf::Color::White);
	////std::cout << "je suis en X" << _position.x << " Y " << _position.y << std::endl;
	_text.setString("[" + std::to_string(static_cast<int>(_position.x)) + ", " + std::to_string(static_cast<int>(_position.y)) + "]");
}

void GameText::setColor(const sf::Color &color)
{
	_text.setFillColor(color);
}

void GameText::setOutline(const sf::Color &color, float thickness)
{
	_text.setOutlineThickness(thickness);
	_text.setOutlineColor(color);
}
