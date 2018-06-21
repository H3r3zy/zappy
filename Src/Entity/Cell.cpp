//
// Created by wisenoa on 12/06/18.
//

#include <SFML/Graphics/RenderWindow.hpp>
#include <SfmlTool.hpp>
#include "Cell.hpp"

Cell::Cell(std::pair<sf::Vector2f, sf::Vector2f> squareDimension, sf::Texture *&texture) : ARectangleShape(squareDimension.first, squareDimension.second), _cellPos(SfmlTool::getArialFont(), _position)
{
//	std::cout << "Je suis une Cell, en [" << _position.x << "," << _position.y << "] et de taille [" << _size.x << "," << _size.y << "]" << std::endl;
	_rectangle.setOutlineThickness(1);
	_rectangle.setOutlineColor(sf::Color::Black);
	_rectangle.setTexture(texture);
	_cellPos.setPosition(_position.x, _position.y + _size.y - _cellPos.getText().getCharacterSize() - 5);
	tmp = _rectangle.getFillColor();
}

Cell::~Cell()
{
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

sf::Text &Cell::getCellPos()
{
//	std::cout << "Ma cll est en :" << _cellPos.getPosition().x << " " << _cellPos.getPosition().y << std::endl;
	return const_cast<sf::Text &>(_cellPos.getText());
}

void Cell::makeTarget()
{
	_rectangle.setFillColor(sf::Color::Red);
}

void Cell::removeTarget()
{
	_rectangle.setFillColor(tmp);
}