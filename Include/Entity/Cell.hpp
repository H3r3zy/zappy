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
#include <SFML/Graphics/Text.hpp>
#include "ARectangleShape.hpp"

class Cell : public ARectangleShape {
	public:
	Cell(std::pair<sf::Vector2f, sf::Vector2f> squareDimension, sf::Texture *&texture);
	~Cell();

	sf::Text &getCellPos();
	void setRessources(unsigned int resourceName, unsigned int number);
	void addRessources(unsigned int resourceName);
	void makeTarget();

	private:
	sf::Text _cellPos;
	sf::Font _font;
	ulong _textureNumber;
	std::map<unsigned int, unsigned int> _ressources;
};

#endif //PSU_ZAPPY_2017_CELL_HPP
