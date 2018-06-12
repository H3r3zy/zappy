//
// Created by wisenoa on 12/06/18.
//


#include "Cell.hpp"

Cell::Cell()
{
}

Cell::Cell(std::pair<sf::Vector2f, sf::Vector2f> squareDimension) : _position(squareDimension.first.x, squareDimension.first.y), _size(squareDimension.second.x, squareDimension.second.y)
{
	std::cout << "Je suis une Cell, en [" << _position.x << "," << _position.y << "] et de taille [" << _size.x << "," << _size.y << "]" << std::endl;
	_cell.setPosition(_position);
	_cell.setSize(_size);
	_cell.setFillColor(sf::Color::Green);
	_cell.setOutlineThickness(1);
	_cell.setOutlineColor(sf::Color::White);
}

Cell::~Cell()
{
}

sf::RectangleShape &Cell::getCell()
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