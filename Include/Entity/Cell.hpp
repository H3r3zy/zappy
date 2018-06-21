//
// Created by wisenoa on 12/06/18.
//


#ifndef PSU_ZAPPY_2017_CELL_HPP
#define PSU_ZAPPY_2017_CELL_HPP

#include <iostream>
#include <unistd.h>
#include <map>
#include <SFML/System.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <Text/GameText.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "ARectangleShape.hpp"

class Cell : public ARectangleShape {
	enum {
		Q0,
		Q1,
		Q2,
		Q3,
		Q4,
		Q5,
		Q6,
	};

	public:
	Cell(std::pair<sf::Vector2f, sf::Vector2f> squareDimension, sf::Texture *&texture, std::vector<sf::Texture> &resourcePack);
	~Cell();

	sf::Text &getCellPos();
	void setRessources(unsigned int resourceName, unsigned int number);
	void addRessources(unsigned int resourceName);
	void printAllResources(sf::RenderWindow &window) const;
	void makeTarget();
	void removeTarget();

	private:
	GameText _cellPos;

	std::map<int, sf::Vector2f> _randomPos;
	std::map<int, bool> _takenPos;

	std::vector<sf::Sprite> _sprite;
	ulong _textureNumber;
	std::map<unsigned int, unsigned int> _ressources;
	sf::Color tmp;

};

#endif //PSU_ZAPPY_2017_CELL_HPP
