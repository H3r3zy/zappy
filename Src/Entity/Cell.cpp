//
// Created by wisenoa on 12/06/18.
//

#include <SFML/Graphics/RenderWindow.hpp>
#include <SfmlTool.hpp>
#include <random>
#include "Cell.hpp"

Cell::Cell(std::pair<sf::Vector2f, sf::Vector2f> squareDimension, sf::Texture *&texture, std::vector<sf::Texture> &resourcePack) : ARectangleShape(squareDimension.first, squareDimension.second), _cellPos(SfmlTool::getArialFont(), _position)
{
	for (int i = 0; i < 14; i++) {
		_sprite.emplace_back(sf::Sprite());
	}

	for (int i = 0; i < 7; i++) {
		_ressources[i];
	}

	std::mt19937 rng;
	rng.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 8);

	_randomPos[0] = sf::Vector2f(0, 0);
	_randomPos[1] = sf::Vector2f(33, 0);
	_randomPos[2] = sf::Vector2f(66, 0);

	_randomPos[3] = sf::Vector2f(33, 0);
	_randomPos[4] = sf::Vector2f(33, 33);
	_randomPos[5] = sf::Vector2f(33, 66);

	_randomPos[6] = sf::Vector2f(66, 0);
	_randomPos[7] = sf::Vector2f(66, 33);
	_randomPos[8] = sf::Vector2f(66, 66);

	for (int i = 0; i < 9; i++) {
		_takenPos[i] = false;
	}
	//sleep(1);

	for (int i = 0; i < 7; i++) {
		auto tmpPos = dist6(rng);

		sf::Vector2f tmp = _randomPos[tmpPos];
		while (_takenPos[tmpPos]) {
			tmpPos++;
			if (tmpPos > 8)
				tmpPos = 0;
			sf::Vector2f tmp = _randomPos[tmpPos];
		}

		_takenPos[tmpPos] = true;

		_sprite[i].setTexture(resourcePack[i]);
		_sprite[i + 7].setTexture(resourcePack[i + 7]);

		_sprite[i].setPosition(_position.x + tmp.x, _position.y + tmp.y);
		_sprite[i + 7].setPosition(_position.x + tmp.x, _position.y + tmp.y);

		_sprite[i].setScale(0.3, 0.3);

		std::cout << std::endl;
	}
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

void Cell::printAllResources(sf::RenderWindow &window) const
{
	for (const auto &it : _ressources) {
		if (it.second == 1) {
			window.draw(_sprite[it.first]);
		} else if (it.second > 1) {
			window.draw(_sprite[it.first + 7]);
		}
//		std::cout << "Il y a dans ma cellule la ressource " << it.first << " et sa quantité " << it.second << std::endl;
	}
}
