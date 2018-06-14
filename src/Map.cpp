//
// Created by wisenoa on 12/06/18.
//

#include "Map.hpp"

Map::Map(int mapsize) : _mapSize(mapsize, mapsize), _gameWindow(sf::VideoMode(1200, 800), "Oh voyage voyage, plus loiiiiin que la nuit et le jour"), _grid(_mapSize)
{
	//_gameWindow.setFramerateLimit(60);
	_windowInfo = new WindowInfo();
	_camera.emplace_back();
	_camera.emplace_back();
	_camera.emplace_back();
	_camera[MAP].reset(sf::FloatRect(0, 0, 1200, 800));
	_camera[HUD].reset(sf::FloatRect(0, 0, 1200, 800));
	_camera[MINIMAP].setViewport(sf::FloatRect(0.75f, 0, 0.25f, 0.25f));
	_playerPos.setPosition(_camera[MAP].getCenter());
	_playerPos.setSize(sf::Vector2f(100, 100));
	_playerPos.setFillColor(sf::Color::Red);

	/* Faking first movement */
	_grid.updateGrid3D(_camera[MAP]);
	_windowInfo->updateInfo(_grid.getNbActive(), _camera[MAP]);
}

void Map::gameLoop()
{
	while (getEvent()) {
		/* Global Display */
		_gameWindow.setView(_camera[MAP]);
		_grid.displayGlobalGrid(_gameWindow, _camera[MAP]);

		/* Minimap Display*/
		_gameWindow.setView(_camera[MINIMAP]);
		_grid.displayMiniGrid(_gameWindow, _camera[MAP]);
		_gameWindow.draw(_playerPos);

		/* HUD DISPLAY */
		_gameWindow.setView(_camera[HUD]);
		_windowInfo->drawInfo(_gameWindow);

		/* Display and Reset */
		_gameWindow.display();
		_gameWindow.clear(sf::Color::Black);
	}
}

bool Map::getEvent()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		_camera[MAP].move(2, 0);
		_playerPos.setPosition(_camera[MAP].getCenter());
		_grid.updateGrid3D(_camera[MAP]);
		_windowInfo->updateInfo(_grid.getNbActive(), _camera[HUD]);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		_camera[MAP].move(-2, 0);
		_playerPos.setPosition(_camera[MAP].getCenter());
		_grid.updateGrid3D(_camera[MAP]);
		_windowInfo->updateInfo(_grid.getNbActive(), _camera[HUD]);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		_camera[MAP].move(0, -2);
		_playerPos.setPosition(_camera[MAP].getCenter());
		_grid.updateGrid3D(_camera[MAP]);
		_windowInfo->updateInfo(_grid.getNbActive(), _camera[HUD]);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		_camera[MAP].move(0, 2);
		_playerPos.setPosition(_camera[MAP].getCenter());
		_grid.updateGrid3D(_camera[MAP]);
		_windowInfo->updateInfo(_grid.getNbActive(), _camera[HUD]);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
		while (sf::Keyboard::isKeyPressed(sf::Keyboard::Z));
			std::cout << " jai appuyé sur Z"<< std::endl;
			_camera[MAP].zoom(0.8f);
		_windowInfo->updateZoom(0.8);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		while (sf::Keyboard::isKeyPressed(sf::Keyboard::A));
		std::cout << " jai appuyé sur Z"<< std::endl;
		_camera[MAP].zoom(1.2f);
		_windowInfo->updateZoom(1.2);
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		_gameWindow.close();
		return false;
	}
	return true;
}
