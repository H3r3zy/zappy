//
// EPITECH PROJECT, 2018
// SfmlTool.cpp
// File description:
// SfmlTool
//

#include <iostream>
#include "SfmlTool.hpp"

sf::Font SfmlTool::arialFont;

const sf::Font &SfmlTool::getArialFont()
{
	return arialFont;
}

bool SfmlTool::InitAllFont()
{
	if (!arialFont.loadFromFile("extra/arial.ttf"))
		return false;
	return true;
}
