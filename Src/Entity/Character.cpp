//
// Created by wisenoa on 15/06/18.
//

#include <SFML/Graphics/RenderWindow.hpp>
#include "Character.hpp"

Character::Character(std::map<char, std::vector<sf::Texture>> &_texturePack, sf::Vector2f &position, uint id) : AMotionShape(position), _id(id)
{
	 _beginTime = std::chrono::system_clock::now();
	for (int i = 0; i < _texturePack[WALK_LEFT].size(); i++) {
		_sprite[WALK_LEFT].emplace_back(sf::Sprite());
		_sprite[WALK_RIGHT].emplace_back(sf::Sprite());
		_sprite[WALK_UP].emplace_back(sf::Sprite());
		_sprite[WALK_DOWN].emplace_back(sf::Sprite());
	}
	for (int i = 0; i < 9; i++) {
		_sprite[WALK_LEFT][i].setTexture(_texturePack[WALK_LEFT][i]);
		_sprite[WALK_RIGHT][i].setTexture(_texturePack[WALK_RIGHT][i]);
		_sprite[WALK_UP][i].setTexture(_texturePack[WALK_UP][i]);
		_sprite[WALK_DOWN][i].setTexture(_texturePack[WALK_DOWN][i]);
	}
	srand(time(NULL));
//	_sprite[WALK_LEFT][0]->setTexture(_texturePack[WALK_LEFT][0]);
}

Character::~Character()
{
}

sf::Sprite &Character::getCharacter()
{
	// 0 => 100 => 7 sec

	if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - _beginTime).count() > 100) {
	//	//std::cout << "il c passé une dixieme de seconde" << std::endl;
		_beginTime = std::chrono::system_clock::now();

		// TODO A DEGAGER
		if (_action) {
			//std::cout << "Le joueur " << _id << " est en action" << std::endl;
			if (_orientation == WALK_LEFT)
				_position.x -= 1.4;
			else if (_orientation == WALK_RIGHT)
				_position.x += 1.4;
			else if (_orientation == WALK_UP)
				_position.y -= 1.4;
			else if (_orientation == WALK_DOWN)
				_position.y += 1.4;

			_actualSprite++;
			if (_actualSprite == 8)
				_actualSprite = 0;


			_testTmp++;
			//std::cout << " le tmp = " << _testTmp << std::endl;
			if (_testTmp == 70) {
				_action = false;
				_testTmp = 0;
			}
	//		std::cout << "je veux le mettre en pos" << _position.x << " " << _position.y << " et son orientation ";
	//		printf("%d\n", _orientation);


		}
		_sprite[_orientation][_actualSprite].setPosition(_position.x, _position.y);
	}


//	//std::cout << "il est en "<< _position.x << " " <<  _position.y << std::endl;

	return _sprite[_orientation][_actualSprite];
}

bool Character::playerLoop(sf::RenderWindow &window)
{
	//std::cout << "coucou" << std::endl;
	auto _beginTime = std::chrono::system_clock::now();
	while (true) {
		if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - _beginTime).count() > 1000) {
			//std::cout << "il c passé une seconde" << std::endl;
			_beginTime = std::chrono::system_clock::now();
//			window.draw(_sprite[WALK_LEFT][_actualSprite]);
		}
	}
}

void Character::setPlayerTeam(const std::string &teamName)
{
	_teamName = teamName;
}

const std::string &Character::getPlayerTeam() const
{
	return _teamName;
}

void Character::setPlayerOrientation(char orientation)
{
	_orientation = orientation;
//	_sprite[orientation][_actualSprite].setPosition(_position.x, _position.y);
}

const char Character::getPlayerOrientation() const
{
	return _orientation;
}

const uint &Character::getPlayerID() const
{
	return _id;
}

void Character::setPlayerLevel(uint level)
{
	_level = level;
}

const uint &Character::getPlayerLevel() const
{
	return _level;
}

void Character::setPlayerMovement(sf::Vector2f &finalPos, uint orientation)
{
	std::cout << "Le joueur " << _id << "a un ontTime aui vaut "  << oneTime << std::endl;

	if (oneTime) {
		_position = _nextPos;
		std::cout << "nextpos = " << _nextPos.x << " " << _nextPos.y << std::endl;
	}
	oneTime = true;
	_testTmp = 0;
	//_orientation = static_cast<char>(orientation);
	_nextPos = finalPos;
	_action = true;
}

const bool Character::getAction() const
{
	return _action;
}
