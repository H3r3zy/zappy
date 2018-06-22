/*
** EPITECH PROJECT, 2018
** client
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <iostream>
#include <unistd.h>
#include <thread>
#include <Tools/Thread.hpp>
#include "Communication.hpp"
#include "SfmlTool.hpp"
#include "Map.hpp"

irc::Map::Map(irc::Communication &comm, bool &displayGui, bool &endClient) : _comm(comm), _displayGui(displayGui), _endClient(endClient), _gameWindow(sf::VideoMode(1, 1), "empty", sf::Style::None), _enqueueMap(_comm), _mapSize(_enqueueMap.ParseMapSize()), _grid(_mapSize, _gameWindow)
{
	SfmlTool::InitAllFont();
	//_gameWindow.setFramerateLimit(60);
	_windowInfo = new WindowInfo();
	initCamera();
	_playerPos.setPosition(_camera[MAP].getCenter() -_camera[MAP].getSize());
	_playerPos.setSize(sf::Vector2f(20, 20));
	_playerPos.setFillColor(sf::Color::Red);

	/* Updating all cells + creating thread for loadingScreen */
	_gameWindow.setActive(false);
	auto thread(new my::Thread([&]() {_enqueueMap.loadingDisplay(_mapSize);}));
	_enqueueMap.fillMap(_grid, _mapSize);
	thread->join();
	_gameWindow.setActive(true);

	_gameWindow.close();
	_gameWindow.create(sf::VideoMode(1200, 800), "Oh voyage voyage, plus loiiiiin que la nuit et le jour");
	_gameWindow.setFramerateLimit(60);
	_gameWindow.setPosition(sf::Vector2i(200, 50));
	//_gameWindow.setFramerateLimit(60); b  b

	_gameWindow.setActive(true);
	/* Faking first movement */
	_playerPos.setPosition(_camera[MAP].getCenter());
	_grid.updateGrid3D(_camera[MAP]);
	_windowInfo->updateInfo(_grid.getNbActive(), _camera[HUD]);


	/* */

}

void irc::Map::initCamera()
{
	_camera.emplace_back();
	_camera.emplace_back();
	_camera.emplace_back();
	_camera[MAP].reset(sf::FloatRect(0, 0, 1200, 800));
	_camera[HUD].reset(sf::FloatRect(0, 0, 1200, 800));
	_camera[MINIMAP].reset(sf::FloatRect(0, 0, 1200, 800));
	_camera[MINIMAP].setViewport(sf::FloatRect(0.66f, 0, 0.25f, 0.25f));
	_camera[MINIMAP].zoom(1.3f);
	_camera[MINIMAP].setCenter(600, -400);
	_camera[MAP].setCenter(600, -400);
}

void irc::Map::loopDisplay()
{
	//std::thread caca(_character[0].playerLoop, _gameWindow);

	while (_gameWindow.isOpen()) {
		_comm.lockDisplay();
		if (!_displayGui && _comm._shack._pos.first != -1 && _comm._shack._pos.second != -1) {
			_grid.getCell(_comm._shack._pos.first, _comm._shack._pos.second)->removeTarget();
			_comm._shack._pos.first = -1;
			_comm._shack._pos.second = -1;
		}
		//std::cout << "je boucle " << std::endl;
		_enqueueMap.parseNextCommand(*this);

		getEvent();
		/* Global Display */
		_gameWindow.setView(_camera[MAP]);
		_grid.displayGlobalGrid(_gameWindow, _camera[MAP]);
		for (auto &it : _character) {
			_gameWindow.draw(it.second.getCharacter());
		}

		/* HUD DISPLAY */
		_gameWindow.setView(_camera[HUD]);
		_windowInfo->drawInfo(_gameWindow);

		/* Minimap Display*/
		_gameWindow.setView(_camera[MINIMAP]);
		_grid.displayMiniGrid(_gameWindow, _camera[MAP], _character);
		_gameWindow.draw(_playerPos);

		/* Display and Reset */
		_gameWindow.display();
		_gameWindow.clear(sf::Color::Black);
		_comm.unlockDisplay();

		std::this_thread::sleep_for(std::chrono::milliseconds(2));
	}
	_endClient = true;
	//caca.detach();
	//caca.std::thread::~thread(); MAYBE
}

bool irc::Map::getEvent()
{
	sf::Event event{};

	// while there are pending events...
//	_comm.loopRead();

	while (_gameWindow.pollEvent(event))
	{
		// check the type of the event...
		switch (event.type)
		{
			// window closed
		case sf::Event::Closed:
			_gameWindow.close();
			return false;
			// key pressed
		case sf::Event::KeyPressed:
			switch (event.key.code) {
			case sf::Keyboard::F:
				_displayGui = true;
				break;
			case sf::Keyboard::Right:
				_camera[MAP].move(10, 0);
				_camera[MINIMAP].move(10, 0);
				_playerPos.setPosition(_camera[MAP].getCenter());
				_grid.updateGrid3D(_camera[MAP]);
				_windowInfo->updateInfo(_grid.getNbActive(), _camera[HUD]);

				break;
			case sf::Keyboard::Left:
				_camera[MAP].move(-10, 0);
				_camera[MINIMAP].move(-10, 0);

				_playerPos.setPosition(_camera[MAP].getCenter());
				_grid.updateGrid3D(_camera[MAP]);
				_windowInfo->updateInfo(_grid.getNbActive(), _camera[HUD]);
				break;
			case sf::Keyboard::Up:

				_camera[MAP].move(0, -10);
				_camera[MINIMAP].move(0, -10);
				_playerPos.setPosition(_camera[MAP].getCenter());
				_grid.updateGrid3D(_camera[MAP]);
				_windowInfo->updateInfo(_grid.getNbActive(), _camera[HUD]);
				break;
			case sf::Keyboard::Down:
				_camera[MAP].move(0, 10);
				_camera[MINIMAP].move(0, 10);
				_playerPos.setPosition(_camera[MAP].getCenter());
				_grid.updateGrid3D(_camera[MAP]);
				_windowInfo->updateInfo(_grid.getNbActive(), _camera[HUD]);
				break;
			case sf::Keyboard::Z:
				_camera[MAP].zoom(0.8f);
				_windowInfo->updateZoom(0.8);
				break;
			case sf::Keyboard::A:
				_camera[MAP].zoom(1.2f);
				_windowInfo->updateZoom(1.2);
				break;
			case sf::Keyboard::Escape:
				_gameWindow.close();
				return false;
			default:
				break;
			}
			break;
		case sf::Event::MouseButtonReleased:
//			//std::cout << "the right button was pressed" << std::endl;


			sf::Vector2i pixelPos = sf::Vector2i(sf::Mouse::getPosition(_gameWindow));

			// convert it to world coordinates
			sf::Vector2f worldPos = _gameWindow.mapPixelToCoords(pixelPos, _camera[MAP]);
/*
			//std::cout << "mouse x: " << event.mouseButton.x << std::endl;
			//std::cout << "mouse y: " << event.mouseButton.y << std::endl;

			//std::cout << "position map" << worldPos.x << " " << worldPos.y << std::endl;



			//std::cout << "=-=-=-==-=-=-==-=-=--=-==-=-" << std::endl;
			//std::cout << "Je regarde si la cellule X: " << (static_cast<int>(worldPos.x / 100)) << " Y: " << static_cast<int>((worldPos.y + 100)* -1 / 100) << "est valide" << std::endl;
			//std::cout << "=-=-=-==-=-=-==-=-=--=-==-=-" << std::endl;

*/
			if (_grid.checkvalid(static_cast<int>(worldPos.x / 100), static_cast<int>((worldPos.y - 100) * -1 / 100))) {
				if (_comm._shack._pos.first != -1 && _comm._shack._pos.second != -1)
					_grid.getCell(_comm._shack._pos.first, _comm._shack._pos.second)->removeTarget();

				_comm._listId.clear();
				if (_comm._shack._pos.first != static_cast<int>(worldPos.x / 100) || _comm._shack._pos.second != static_cast<int>((worldPos.y - 100) * -1 / 100)) {
					_grid.getCell(static_cast<int>(worldPos.x / 100), static_cast<int>((worldPos.y - 100) * -1 / 100))->makeTarget();
					_comm._listId.push_back(-1);
					_displayGui = true;
					_comm._shack._pos.first = static_cast<int>(worldPos.x / 100);
					_comm._shack._pos.second = static_cast<int>((worldPos.y - 100) * -1 / 100);
				} else {
					_comm._shack._pos.first = -1;
					_comm._shack._pos.second = -1;
				}
				// Todo: Add list player on it

				//std::cout << "je creer un perso en" << worldPos.x << " " << worldPos.y << std::endl;
				//_character.emplace_back(_grid.getTextureCharacter(), worldPos);

				//std::cout << "jai reussit" << std::endl;
			}

			break;

		}
		return true;

	}
	return true;



	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
		while (sf::Keyboard::isKeyPressed(sf::Keyboard::Z));
		//std::cout << " jai appuyé sur Z"<< std::endl;

	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		while (sf::Keyboard::isKeyPressed(sf::Keyboard::A));
		//std::cout << " jai appuyé sur Z"<< std::endl;
		_camera[MAP].zoom(1.2f);
		_windowInfo->updateZoom(1.2);
	}
	return true;
}

std::map<uint, Character> &irc::Map::getCharacterMap()
{
	return _character;
}

Grid &irc::Map::getGrid()
{
	return _grid;
}
