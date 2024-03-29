//
// EPITECH PROJECT, 2018
// Water.cpp
// File description:
// Water
//

#include "Water.hpp"

Water::Water(sf::Vector2f &position, std::vector<sf::Texture> &texturePack) : AMotionShape(position)
{
	_sprite[0].emplace_back(sf::Sprite());
	_sprite[0].emplace_back(sf::Sprite());
	_sprite[0].emplace_back(sf::Sprite());
	_sprite[0].emplace_back(sf::Sprite());
	_beginTime = std::chrono::system_clock::now();

	int i = 0;
	while (i < 4) {
		_sprite[0][i].setTexture(texturePack[i]);
		_sprite[0][i].setPosition(position);
		i++;
	}
}

 sf::Sprite Water::getSprite()
{
	if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - _beginTime).count() > 250) {
		_beginTime = std::chrono::system_clock::now();
		_actualSprite++;
		if (_actualSprite == 4) {
			_actualSprite = 0;
		}
	}
	return _sprite[0][_actualSprite];
}
