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
	// TODO delete map
}

void Grid::updateGrid3D(sf::View &view)
{
	_activeMap.clear();
	sf::Vector2f chunk;
	chunk.x = (view.getCenter().x / 100) - 20;
	chunk.y = (view.getCenter().y / 100) - 20;
	sf::Vector2f to = chunk;
	to.x += 40;
	to.y += 40;
	while (chunk.y < to.y) {
		if (chunk.x >= 0 && chunk.y >= 0) {
			if (_gameMap.find(POSITION(static_cast<const uint &>(chunk.x), static_cast<const uint &>(chunk.y))) != _gameMap.end()) {
				_activeMap.push_back(_gameMap[POSITION(static_cast<const uint &>(chunk.x), static_cast<const uint &>(chunk.y))]);
			}
		}
		chunk.x++;
		if (chunk.x >= to.x) {
			chunk.x = (view.getCenter().x / 100) - 20;
			chunk.y++;
		}
	}

}

void Grid::displayGlobalGrid(sf::RenderWindow &window, const sf::View &view)
{
	for (const auto &it : _activeMap) {
		window.draw(it->getCell());
	}
}
