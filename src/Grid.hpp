//
// Created by wisenoa on 13/06/18.
//


#ifndef PSU_ZAPPY_2017_GRID_HPP
#define PSU_ZAPPY_2017_GRID_HPP

#include <SFML/System.hpp>
#include <map>
#include <random>
#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Cell.hpp"

class Grid {

	enum {
		GRASS,
		GRASS1,
		GRASS2,
		GRASS3,
		GRASS4
	};

	typedef std::pair<uint, uint> 				POSITION;
	typedef std::map<std::pair<uint, uint>, Cell *>  	GRID_MAP;

	public:
	Grid(const sf::Vector2f &mapSize);
	void displayGlobalGrid(sf::RenderWindow &window, const sf::View &view);
	void displayMiniGrid(sf::RenderWindow &window, const sf::View &view);
	void updateGrid3D(sf::View &view);
	uint getNbActive() const;
	bool checkvalid(int x, int y);
	Cell *&getCell(int x, int y);
	~Grid();

	private:
	bool loadTextures();
	void loadMap();

	/* TOOLS */
	sf::Vector2f _mapSize;
	std::vector<Cell *> _activeMap;
	uint _nbActive;
	std::map<std::pair<uint, uint>, Cell *> _gameMap;

	/*  SFML */
	std::vector<sf::Texture *> _texturePack;
};

#endif //PSU_ZAPPY_2017_GRID_HPP