//
// Created by wisenoa on 12/06/18.
//


#ifndef PSU_ZAPPY_2017_MAP_HPP
#define PSU_ZAPPY_2017_MAP_HPP

#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include "Grid.hpp"
#include "WindowInfo.hpp"

class Map {
	public:
	Map(int mapSize);
	~Map() = default;

	void gameLoop();

	private:
	bool getEvent();
	sf::Vector2f _mapSize;

	/* Member Classes */
	Grid _grid;
	WindowInfo _windowInfo;

	/* SFML */
	sf::Event _event;
	sf::RectangleShape _playerPos;
	/* std::pair<Global camera, Minimap camera >*/
	std::pair<sf::View, sf::View> _camera;
	sf::RenderWindow _gameWindow;
};

#endif //PSU_ZAPPY_2017_MAP_HPP
