//
// Created by wisenoa on 12/06/18.
//

#include <thread>
#include <SfmlTool.hpp>
#include "Map.hpp"

Map::Map(int mapsize) : _mapSize(mapsize, mapsize), _gameWindow(sf::VideoMode(1200, 800), "Oh voyage voyage, plus loiiiiin que la nuit et le jour"), _grid(_mapSize)
{
	SfmlTool::InitAllFont();
	//_gameWindow.setFramerateLimit(60);
	_windowInfo = new WindowInfo();
	initCamera();
	_playerPos.setPosition(_camera[MAP].getCenter() -_camera[MAP].getSize());
	_playerPos.setSize(sf::Vector2f(20, 20));
	_playerPos.setFillColor(sf::Color::Red);


	/* Faking first movement */
	_grid.updateGrid3D(_camera[MAP]);
	_windowInfo->updateInfo(_grid.getNbActive(), _camera[MAP]);

	/* Coucou je crer un thread */
	sf::Vector2f tmp = {1000, 0};
	_character.emplace_back(_grid.getTextureCharacter(), tmp);
	tmp.x -= 500;
	tmp.y -= 1000;
	_character.emplace_back(_grid.getTextureCharacter(), tmp);

	/* */
}


void Map::initCamera()
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

void Map::gameLoop()
{
	//std::thread caca(_character[0].playerLoop, _gameWindow);


	while (getEvent()) {

		/* Global Display */
		_gameWindow.setView(_camera[MAP]);
		_grid.displayGlobalGrid(_gameWindow, _camera[MAP]);
		for (auto &it : _character) {
			_gameWindow.draw(it.getCharacter());
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
	}
	//caca.detach();
	//caca.std::thread::~thread(); MAYBE
}

bool Map::getEvent()
{
	sf::Event event{};

	// while there are pending events...
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
				std::cout << "the right button was pressed" << std::endl;


			sf::Vector2i pixelPos = sf::Vector2i(sf::Mouse::getPosition(_gameWindow));

			// convert it to world coordinates
			sf::Vector2f worldPos = _gameWindow.mapPixelToCoords(pixelPos, _camera[MAP]);

			std::cout << "mouse x: " << event.mouseButton.x << std::endl;
			std::cout << "mouse y: " << event.mouseButton.y << std::endl;

			std::cout << "position map" << worldPos.x << " " << worldPos.y << std::endl;



			std::cout << "=-=-=-==-=-=-==-=-=--=-==-=-" << std::endl;
			std::cout << "Je regarde si la cellule X: " << (static_cast<int>(worldPos.x / 100)) << " Y: " << static_cast<int>((worldPos.y + 100)* -1 / 100) << "est valide" << std::endl;
			std::cout << "=-=-=-==-=-=-==-=-=--=-==-=-" << std::endl;


			if (_grid.checkvalid(static_cast<int>(worldPos.x / 100), static_cast<int>((worldPos.y - 100) * -1 / 100))) {
				_grid.getCell(static_cast<int>(worldPos.x / 100), static_cast<int>((worldPos.y - 100) * -1 / 100))->makeTarget();

				std::cout << "je creer un perso en" << worldPos.x << " " << worldPos.y << std::endl;
				_character.emplace_back(_grid.getTextureCharacter(), worldPos);

				std::cout << "jai reussit" << std::endl;
			}

			break;

		}
		return true;

	}
	return true;



	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
		while (sf::Keyboard::isKeyPressed(sf::Keyboard::Z));
			std::cout << " jai appuyé sur Z"<< std::endl;

	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		while (sf::Keyboard::isKeyPressed(sf::Keyboard::A));
		std::cout << " jai appuyé sur Z"<< std::endl;
		_camera[MAP].zoom(1.2f);
		_windowInfo->updateZoom(1.2);
	}
	return true;
}
