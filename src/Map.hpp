//
// Created by wisenoa on 12/06/18.
//


#ifndef PSU_ZAPPY_2017_MAP_HPP
#define PSU_ZAPPY_2017_MAP_HPP

#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Grid.hpp"

class Map {
	public:
	Map(int mapSize);
	~Map() = default;

	void gameLoop();

	private:
	sf::Vector2f _mapSize;
	Grid _grid;
	sf::RenderWindow _window;
};

#endif //PSU_ZAPPY_2017_MAP_HPP
