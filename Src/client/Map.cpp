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

zap::Map::Map(zap::Communication &comm, bool &displayGui, bool &endClient) : _comm(comm), _displayGui(displayGui), _endClient(endClient), _gameWindow(sf::VideoMode(1200, 800), "Zappy"), _enqueueMap(_comm), _mapSize(_enqueueMap.ParseMapSize()), _teamName(_enqueueMap.getTeam()), _grid(_mapSize, _gameWindow, _teamName)
{
	_comm._teamName = _teamName;
	SfmlTool::InitAllFont();
	//_gameWindow.setFramerateLimit(60);
	_windowInfo = new WindowInfo();
	initCamera();
	_playerPos.setPosition(_camera[MAP].getCenter() -_camera[MAP].getSize());
	_playerPos.setSize(sf::Vector2f(20, 20));
	_playerPos.setFillColor(sf::Color::Red);

	/* Updating all cells + creating thread for loadingScreen */
	_gameWindow.setActive(false);
	auto thread(new my::Thread([&]() {
		try {
			_enqueueMap.loadingDisplay(_mapSize, _gameWindow);
		} catch (const std::exception &e) {
		}
	}));
	_enqueueMap.fillMap(*this, _mapSize);
	thread->join();
	_gameWindow.setActive(true);
	_gameWindow.setPosition(sf::Vector2i(200, 50));
	//_gameWindow.setFramerateLimit(60); b  b

	/* Faking first movement */
	_playerPos.setPosition(_camera[MAP].getCenter());
	_grid.updateGrid3D(_camera[MAP]);
	_windowInfo->updateInfo(_grid.getNbActive(), _camera[HUD]);
	initColorTeam();
}

void zap::Map::initCamera()
{
	_camera.emplace_back();
	_camera.emplace_back();
	_camera.emplace_back();
	_camera[MAP].reset(sf::FloatRect(0, 0, 1200, 800));
	_camera[HUD].reset(sf::FloatRect(0, 0, 1200, 800));
	_camera[MINIMAP].reset(sf::FloatRect(0, 0, 1200, 800));
	_camera[MINIMAP].setViewport(sf::FloatRect(0.66f, 0, 0.25f, 0.25f));
	_camera[MINIMAP].zoom(1.3f);
	_camera[MINIMAP].setCenter(600, 400);
	_camera[MAP].setCenter(600, 400);
}

void zap::Map::updateGuiData()
{
	if ((!_displayGui || _comm._listId.empty()) && _comm._shack._pos.first != -1 && _comm._shack._pos.second != -1) {
		_grid.getCell(_comm._shack._pos.first, _comm._shack._pos.second)->removeTarget();
		_comm._shack._pos.first = -1;
		_comm._shack._pos.second = -1;
	}
	_comm._shack.player_on = 0;
	for (auto && it : _character) {
		auto pos = it.second.getPosition();
		if (pos.x > (_comm._shack._pos.first * 100) - 30 && pos.x < (_comm._shack._pos.first * 100) + 70 && pos.y > (_comm._shack._pos.second * 100) - 50 && pos.y < (_comm._shack._pos.second * 100) + 50)
			_comm._shack.player_on++;
		if (it.second.getPlayerID() == static_cast<ulong>(_comm._player.id)) {
			_comm._player.level = it.second.getPlayerLevel();
			_comm._player.team = it.second.getPlayerTeam();
			_comm._player._pos.first = pos.x;
			_comm._player._pos.second = pos.y;
		}
	}
}

void zap::Map::loopDisplay()
{
	while (_gameWindow.isOpen() && !_endClient) {
		_comm.lockDisplay();
		updateGuiData();
		_enqueueMap.parseNextCommand(*this);
		getEvent();
		_gameWindow.setView(_camera[MAP]);
		_grid.displayGlobalGrid(_gameWindow, _camera[MAP]);
		_comm.lockMap();
		for (auto &it : _character) {
			_gameWindow.draw(it.second.getCharacter());
		}
		_comm.unlockMap();

		/* HUD DISPLAY */
		_gameWindow.setView(_camera[HUD]);
		_windowInfo->drawInfo(_gameWindow);

		/* Minimap Display*/
		_gameWindow.setView(_camera[MINIMAP]);
		_grid.displayMiniGrid(_gameWindow, _camera[MAP], _character, _teamColor);
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

bool zap::Map::getEvent()
{
	sf::Event event{};

	// while there are pending events...
//	_comm.loopRead();

	while (_gameWindow.pollEvent(event))
	{
		// check the type of the event...
		switch (event.type) {
			// window closed
		case sf::Event::Closed: {
			_gameWindow.close();
			return false;
			// key pressed
		}
		case sf::Event::KeyPressed: {
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
		}
		case sf::Event::MouseButtonReleased: {
			sf::Vector2i pixelPos = sf::Vector2i(sf::Mouse::getPosition(_gameWindow));
			sf::Vector2f worldPos = _gameWindow.mapPixelToCoords(pixelPos, _camera[MAP]);
			if (_grid.checkvalid(static_cast<int>(worldPos.x / 100), static_cast<int>((worldPos.y) / 100))) {
				if (_comm._shack._pos.first != -1 && _comm._shack._pos.second != -1)
					_grid.getCell(_comm._shack._pos.first, _comm._shack._pos.second)->removeTarget();

				_comm._listId.clear();
				if (_comm._shack._pos.first != static_cast<int>(worldPos.x / 100) || _comm._shack._pos.second != static_cast<int>((worldPos.y) / 100)) {
					_grid.getCell(static_cast<int>(worldPos.x / 100), static_cast<int>((worldPos.y) / 100))->makeTarget();
					_comm._listId.push_back(-1);
					_displayGui = true;
					_comm._shack._pos.first = static_cast<int>(worldPos.x / 100);
					_comm._shack._pos.second = static_cast<int>((worldPos.y) / 100);
					for (auto && it : _character) {
						auto pos = it.second.getPosition();
						if (pos.x > (_comm._shack._pos.first * 100) - 30 && pos.x < (_comm._shack._pos.first * 100) + 70 && pos.y > (_comm._shack._pos.second * 100) - 50 && pos.y < (_comm._shack._pos.second * 100) + 50)
							_comm._listId.push_back(it.second.getPlayerID());
					}

				} else {
					_comm._shack._pos.first = -1;
					_comm._shack._pos.second = -1;
				}
			}
			break;
		}
		default:
			break;

		}
		return true;

	}
	return true;
}

std::map<uint, Character> &zap::Map::getCharacterMap()
{
	return _character;
}

Grid &zap::Map::getGrid()
{
	return _grid;
}

void zap::Map::initColorTeam()
{
	std::mt19937 rng;
	rng.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 255);

	sf::Color color;
	for (auto &it : _teamName) {
		color.r = static_cast<sf::Uint8>(dist6(rng));
		color.g = static_cast<sf::Uint8>(dist6(rng));
		color.b = static_cast<sf::Uint8>(dist6(rng));
		_teamColor[it] = color;
	}
}

zap::Communication &zap::Map::getComm()
{
	return _comm;
}

const sf::Vector2f &zap::Map::getMapSize() const
{
	return _mapSize;
}

const std::vector<std::string> &zap::Map::getTeamName() const
{
	return _teamName;
}

std::map<int, std::pair<std::string, sf::Vector2i>> &zap::Map::getEggMap()
{
	return _egg;
}
