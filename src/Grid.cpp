//
// Created by wisenoa on 13/06/18.
//


#include "Grid.hpp"

Grid::Grid(const sf::Vector2f &mapSize) : _mapSize(mapSize)
{
	std::pair<sf::Vector2f, sf::Vector2f> dimension;
	dimension.second.x = 100;
	dimension.second.y = 100;
	for (uint j = 0; j < _mapSize.y; j++) {
		for (uint i = 0; i < _mapSize.x; i++) {
			dimension.first.x = i * 100;
			dimension.first.y = j * 100;
			_gameMap.insert(GRID_MAP::value_type(POSITION(i, j), new Cell(dimension)));
		}
	}
}

Grid::~Grid()
{
}

void Grid::displayGrid(sf::RenderWindow &window)
{
	for (const auto &it : _gameMap) {
		window.draw(it.second->getCell());
	}
}
