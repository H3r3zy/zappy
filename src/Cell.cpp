//
// Created by wisenoa on 12/06/18.
//


#include <SFML/Graphics/RenderWindow.hpp>
#include "Cell.hpp"

Cell::Cell()
{
}

Cell::Cell(std::pair<sf::Vector2f, sf::Vector2f> squareDimension) : _position(squareDimension.first.x, squareDimension.first.y * - 1), _size(squareDimension.second.x, squareDimension.second.y)
{
	std::cout << "Je suis une Cell, en [" << _position.x << "," << _position.y << "] et de taille [" << _size.x << "," << _size.y << "]" << std::endl;
	_cell.setPosition(_position);
	_cell.setSize(_size);
	_cell.setFillColor(sf::Color::Green);
	_cell.setOutlineThickness(1);
	_cell.setOutlineColor(sf::Color::White);
	_stringPos = "[" + std::to_string(static_cast<int>(_position.x)) + ", " + std::to_string(static_cast<int>(_position.y)) + "]";
}

Cell::~Cell()
{
}

sf::RectangleShape &Cell::drawCell()
{
	return _cell;
}

void Cell::setRessources(unsigned int resourceName, unsigned int number)
{
	for (auto &&it : _ressources) {
		if (it.first == resourceName) {
			it.second = number;
			break;
		}
	}
}

void Cell::addRessources(unsigned int resourceName)
{
	for (auto &&it : _ressources) {
		if (it.first == resourceName) {
			++it.second;
			break;
		}
	}
}

sf::Vector2f &Cell::getPos()
{
	return _position;
}

std::string &Cell::getStringPos()
{
	return _stringPos;
}
