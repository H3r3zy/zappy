//
// Created by wisenoa on 12/06/18.
//


#include "Map.hpp"

Map::Map(int mapsize) : _mapSize(mapsize, mapsize), _grid(_mapSize)
{
	_window.create(sf::VideoMode(1200, 800), "Oh voyage voyage, plus loiiiiin que la nuit et le jour");
	_window.setFramerateLimit(60);
	_camera.first.reset(sf::FloatRect(0, 0, 1200, 800));
	_camera.second.setViewport(sf::FloatRect(0.75f, 0, 0.25f, 0.25f));
}

void Map::gameLoop()
{
	while (_window.isOpen()) {

		/* Global Display */
		_window.setView(_camera.first);
		_grid.displayGrid(_window);
		_window.draw(_windowInfo.getFPS());

		/* Minimap Display*/
		_window.setView(_camera.second);
		_grid.displayGrid(_window);
		_window.display();
		_window.clear(sf::Color::Black);
		getEvent();
	}
}

void Map::getEvent()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		std::cout << "[USER]" << "Pressed Right Key" << std::endl;
		_camera.first.move(2, 0);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		std::cout << "[USER]" << "Pressed Left Key" << std::endl;
		_camera.first.move(-2, 0);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		std::cout << "[USER]" << "Pressed Up Key" << std::endl;
		_camera.first.move(0, -2);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		std::cout << "[USER]" << "Pressed Down Key" << std::endl;
		_camera.first.move(0, 2);
	}
	else if (_event.type == sf::Event::Closed)
		_window.close();
}