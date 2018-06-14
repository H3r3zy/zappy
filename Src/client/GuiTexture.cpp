/*
** EPITECH PROJECT, 2018
** client
** File description:
** Created by martin.januario@epitech.eu,
*/

#include "GuiTexture.hpp"

void irc::GuiTexture::initTexture()
{
	auto bck = new irc::Square(sf::IntRect(0, 0, WIDTH, HEIGHT));
	bck->setColor(sf::Color(66, 66, 66, 255));
	_monitor->addObjectToDraw("background", bck);
}