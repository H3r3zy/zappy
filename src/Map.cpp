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
		_window.draw(_windowInfo.getFPS());
		//getEvent();
		_window.display();
	}
}

void Map::getEvent()
{
	if (_window.pollEvent(_event)) {
		// Request for closing the window
		if (_event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			_window.close();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			std::cout << "jai appuye a droite" << std::endl;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			std::cout << "jai appuye a droite" << std::endl;
		}
	}
}