//
// Created by wisenoa on 12/06/18.
//


#include "Map.hpp"

Map::Map(int mapsize) : _mapSize(mapsize, mapsize), _gameWindow(sf::VideoMode(1200, 800), "Oh voyage voyage, plus loiiiiin que la nuit et le jour"), _grid(_mapSize)
{
	//_gameWindow.setFramerateLimit(60);
	_camera.first.reset(sf::FloatRect(0, 0, 1200, 800));
	_camera.second.setViewport(sf::FloatRect(0.75f, 0, 0.25f, 0.25f));
	_playerPos.setPosition(_camera.first.getCenter());
	_playerPos.setSize(sf::Vector2f(100, 100));
	_playerPos.setFillColor(sf::Color::Red);
	_grid.updateGrid3D(_camera.first);
}

void Map::gameLoop()
{
	while (getEvent()) {
		/* Global Display */
		_gameWindow.setView(_camera.first);

		_grid.displayGlobalGrid(_gameWindow, _camera.first);
		_gameWindow.draw(_windowInfo.getFPS(_camera.first));

		/* Minimap Display*/
		_gameWindow.setView(_camera.second);
		//_grid.displayGlobalGrid(_gameWindow, _camera.first);
		_gameWindow.draw(_playerPos);
		/* Display and Reset */
		_gameWindow.display();
		_gameWindow.clear(sf::Color::Black);
	}
}

bool Map::getEvent()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		_camera.first.move(2, 0);
		_playerPos.setPosition(_camera.first.getCenter());
		_grid.updateGrid3D(_camera.first);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		_camera.first.move(-2, 0);
		_playerPos.setPosition(_camera.first.getCenter());
		_grid.updateGrid3D(_camera.first);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		_camera.first.move(0, -2);
		_playerPos.setPosition(_camera.first.getCenter());
		_grid.updateGrid3D(_camera.first);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		_camera.first.move(0, 2);
		_playerPos.setPosition(_camera.first.getCenter());
		_grid.updateGrid3D(_camera.first);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		_gameWindow.close();
		return false;
	}
	return true;
}
