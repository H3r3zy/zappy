//
// Created by wisenoa on 13/06/18.
//


#ifndef PSU_ZAPPY_2017_GRID_HPP
#define PSU_ZAPPY_2017_GRID_HPP

#include <SFML/System.hpp>
#include <map>
#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Cell.hpp"

class Grid {

	typedef std::pair<uint, uint> 				POSITION;
	typedef std::map<std::pair<uint, uint>, Cell *>  	GRID_MAP;

	public:
	Grid(const sf::Vector2f &mapSize);
	void displayGlobalGrid(sf::RenderWindow &window, const sf::View &view);
	void updateGrid3D(sf::View &view);
	uint getNbActive() const;
	~Grid();

	private:
	sf::Vector2f _mapSize;
	std::vector<Cell *> _activeMap;
	sf::Font _font;
	sf::Text _text;
	uint _nbActive;
	std::map<std::pair<uint, uint>, Cell *> _gameMap;
};

#endif //PSU_ZAPPY_2017_GRID_HPP