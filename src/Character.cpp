//
// Created by wisenoa on 15/06/18.
//

#include <SFML/Graphics/RenderWindow.hpp>
#include "Character.hpp"

Character::Character(std::map<char, std::vector<sf::Texture>> &_texturePack) :_actualSprite(0)
{
	_position = {10, 0};
	for (int i = 0; i < 9; i++)
		_sprite[WALK_LEFT].emplace_back(sf::Sprite());
	int i = 0;
	while (i < 9) {
		_sprite[WALK_LEFT][i].setTexture(_texturePack[WALK_LEFT][i]);
		i++;
	}
//	_sprite[WALK_LEFT][0]->setTexture(_texturePack[WALK_LEFT][0]);
}

sf::Sprite &Character::getCharacter()
{
	_actualSprite++;
	if (_actualSprite == 9)
		_actualSprite = 0;
	return _sprite[WALK_LEFT][_actualSprite];
}

Character::~Character()
{
}

bool Character::playerLoop(sf::RenderWindow &window)
{
	std::cout << "coucou" << std::endl;
	auto _beginTime = std::chrono::system_clock::now();
	while (true) {
		if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - _beginTime).count() > 1000) {
			std::cout << "il c passé une seconde" << std::endl;
			_beginTime = std::chrono::system_clock::now();
//			window.draw(_sprite[WALK_LEFT][_actualSprite]);
		}
	}
}
