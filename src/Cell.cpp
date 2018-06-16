//
// Created by wisenoa on 12/06/18.
//


#include <SFML/Graphics/RenderWindow.hpp>
#include "Cell.hpp"

Cell::Cell()
{
}

Cell::Cell(std::pair<sf::Vector2f, sf::Vector2f> squareDimension, sf::Texture *&texture) : _position(squareDimension.first.x, squareDimension.first.y * - 1), _size(squareDimension.second.x, squareDimension.second.y)
{
	std::cout << "Je suis une Cell, en [" << _position.x << "," << _position.y << "] et de taille [" << _size.x << "," << _size.y << "]" << std::endl;
	_cell.setPosition(_position);
	_cell.setSize(_size);
	_cell.setOutlineThickness(1);
	_cell.setOutlineColor(sf::Color::Black);
	_cell.setTexture(texture);
	_font.loadFromFile("arial.ttf");
	_cellPos.setFont(_font);
	_cellPos.setFillColor(sf::Color::White);
	_cellPos.setCharacterSize(12);
	_cellPos.setString("[" + std::to_string(static_cast<int>(_position.x)) + ", " + std::to_string(static_cast<int>(_position.y)) + "]");
	_cellPos.setPosition(_position.x, _position.y + _size.y - _cellPos.getCharacterSize() - 5);
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

sf::Text &Cell::getCellPos()
{
	return _cellPos;
}

void Cell::makeTarget()
{
	_cell.setFillColor(sf::Color::Red);
}
