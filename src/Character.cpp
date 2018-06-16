//
// Created by wisenoa on 15/06/18.
//

#include <SFML/Graphics/RenderWindow.hpp>
#include "Character.hpp"

Character::Character(std::map<char, std::vector<sf::Texture>> &_texturePack, sf::Vector2f &position) :_actualSprite(0), _position(position)
{
	 _beginTime = std::chrono::system_clock::now();
	for (int i = 0; i < 9; i++) {
		_sprite[WALK_LEFT].emplace_back(sf::Sprite());
		_sprite[WALK_RIGHT].emplace_back(sf::Sprite());
		_sprite[WALK_UP].emplace_back(sf::Sprite());
		_sprite[WALK_DOWN].emplace_back(sf::Sprite());
	}
	int i = 0;
	while (i < 9) {
		_sprite[WALK_LEFT][i].setTexture(_texturePack[WALK_LEFT][i]);
		_sprite[WALK_RIGHT][i].setTexture(_texturePack[WALK_RIGHT][i]);
		_sprite[WALK_UP][i].setTexture(_texturePack[WALK_UP][i]);
		_sprite[WALK_DOWN][i].setTexture(_texturePack[WALK_DOWN][i]);
		i++;
	}
	srand(time(NULL));
//	_sprite[WALK_LEFT][0]->setTexture(_texturePack[WALK_LEFT][0]);
}

sf::Sprite &Character::getCharacter()
{
	// 0 => 100 => 7 sec

	if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - _beginTime).count() > 100) {
	//	std::cout << "il c passé une dixieme de seconde" << std::endl;
		_beginTime = std::chrono::system_clock::now();
		_sprite[_randomDirection][_actualSprite].setPosition(_position.x, _position.y);


		// TOODO A DEGAGER
		if (_randomDirection == WALK_LEFT)
			_position.x -= 1.4;
		else if (_randomDirection == WALK_RIGHT)
			_position.x += 1.4;
		else if (_randomDirection == WALK_UP)
			_position.y -= 1.4;
		else if (_randomDirection == WALK_DOWN)
			_position.y += 1.4;

		_actualSprite++;
		_testTmp++;

	}

	if (_testTmp == 70) {
		_testTmp = 0;
		_randomDirection = rand() % 4;
	}

//	std::cout << "il est en "<< _position.x << " " <<  _position.y << std::endl;
	if (_actualSprite == 8)
		_actualSprite = 0;

	_sprite[_randomDirection][_actualSprite].setPosition(_position.x, _position.y);
	return _sprite[_randomDirection][_actualSprite];
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
