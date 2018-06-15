//
// EPITECH PROJECT, 2018
// main.cpp
// File description:
// main
//

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Map.hpp"

int main(int ac, char **av)
{
	Map *map = new Map(std::stoi(av[1]));

	map->gameLoop();

}