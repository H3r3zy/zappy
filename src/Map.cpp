//
// Created by wisenoa on 12/06/18.
//


#include "Map.hpp"

Map::Map(int mapsize) : _mapSize(mapsize, mapsize), _grid(_mapSize)
{
	_window.create(sf::VideoMode(800, 600), "SFML window");
}

void Map::gameLoop()
{
	while (_window.isOpen()) {
		_window.clear(sf::Color::Black);
		_grid.displayGrid(_window);
		_window.display();
	}
}