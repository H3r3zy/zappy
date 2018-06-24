//
// EPITECH PROJECT, 2018
// GameText.cpp
// File description:
// GameText
//

#include <iostream>
#include "Text/GameText.hpp"

GameText::GameText(const sf::Font &font, sf::Vector2f &position) : AText(font, position, 12)
{
	_text.setFillColor(sf::Color::White);
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
