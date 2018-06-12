//
// Created by wisenoa on 12/06/18.
//


#ifndef PSU_ZAPPY_2017_CELL_HPP
#define PSU_ZAPPY_2017_CELL_HPP

#include <iostream>
#include <map>
#include <SFML/System.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class Cell {
	public:
	Cell();
	Cell(std::pair<sf::Vector2f, sf::Vector2f> squareDimension);
	~Cell();
	sf::RectangleShape &getCell();
	void setRessources(unsigned int resourceName, unsigned int number);
	void addRessources(unsigned int resourceName);

	private:
	sf::Vector2f _position;
	sf::Vector2f _size;
	sf::RectangleShape _cell;
	std::map<unsigned int, unsigned int> _ressources;
};

#endif //PSU_ZAPPY_2017_CELL_HPP
