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
	void getEvent();
	sf::Vector2f _mapSize;
	Grid _grid;
	WindowInfo _windowInfo;
	sf::RenderWindow _window;
	sf::Event _event;
};

#endif //PSU_ZAPPY_2017_MAP_HPP
