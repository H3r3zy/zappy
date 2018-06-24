//
// EPITECH PROJECT, 2018
// Character.cpp
// File description:
// Character
//

#include <SFML/Graphics/RenderWindow.hpp>
#include "Character.hpp"
#include <unistd.h>

Character::Character(std::map<char, std::vector<sf::Texture>> &_texturePack, sf::Vector2f &position, uint id, int freq, const sf::Vector2f &mapSize, const std::string &teamName) : AMotionShape(position), _mapSize(mapSize), _id(id), _freq(freq)
{
	_teamName = teamName;
	 _beginTime = std::chrono::system_clock::now();
	for (int i = 0; i < 9; i++) {
		_sprite[WALK_LEFT].emplace_back(sf::Sprite());
		_sprite[WALK_RIGHT].emplace_back(sf::Sprite());
		_sprite[WALK_UP].emplace_back(sf::Sprite());
		_sprite[WALK_DOWN].emplace_back(sf::Sprite());
		_sprite[TAKE].emplace_back(sf::Sprite());
		_sprite[INCANT].emplace_back(sf::Sprite());
		_sprite[BROADCAST].emplace_back(sf::Sprite());
		_sprite[EGG].emplace_back(sf::Sprite());
	}
	for (int i = 0; i < 9; i++) {
		_sprite[WALK_LEFT][i].setTexture(_texturePack[WALK_LEFT][i]);
		_sprite[WALK_RIGHT][i].setTexture(_texturePack[WALK_RIGHT][i]);
		_sprite[WALK_UP][i].setTexture(_texturePack[WALK_UP][i]);
		_sprite[WALK_DOWN][i].setTexture(_texturePack[WALK_DOWN][i]);
		_sprite[TAKE][i].setTexture(_texturePack[TAKE][i]);
		_sprite[INCANT][i].setTexture(_texturePack[INCANT][i]);
		_sprite[BROADCAST][i].setTexture(_texturePack[BROADCAST][i]);
		_sprite[EGG][i].setTexture(_texturePack[EGG][i]);
	}
	usleep(100);
	srand(time(NULL));
}

Character::~Character()
{
}

sf::Sprite &Character::getCharacter()
{
	if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - _beginTime).count() > (100 / _freq)) {
		double savetime = (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - _beginTime).count()) / _duration;
		if (_action) {
			savetime *= _freq;
			savetime /= 10;
			if (_orientation == WALK_LEFT)
				_position.x -= savetime;
			else if (_orientation == WALK_RIGHT)
				_position.x += savetime;
			else if (_orientation == WALK_UP)
				_position.y -= savetime;
			else if (_orientation == WALK_DOWN)
				_position.y += savetime;

			if (_nextFrameTime == _freq) {
				_actualSprite++;
				_nextFrameTime = 0;
			} else {
				_nextFrameTime++;
			}
			if (_actualSprite == 8)
				_actualSprite = 0;
			_totalDist += savetime;
			if (_totalDist >= 100) {
				_action = false;
				_totalDist = 0;
			}
			checkOutMap();

		}
		if (savetime != 0)
			_beginTime = std::chrono::system_clock::now();
		_sprite[_orientation][_actualSprite].setPosition(_position.x, _position.y);
	}
	return _sprite[_orientation][_actualSprite];
}

void Character::setPlayerTeam(const std::string &teamName)
{
	_teamName = teamName;
}

const std::string &Character::getPlayerTeam() const
{
	return _teamName;
}

void Character::setPlayerOrientation(char orientation, int duration)
{
	if (oneTime) {
		_position = _nextPos;
	}
	_duration = duration;
	_orientation = orientation;
	_totalDist = 0;
	_actualSprite = 0;
}

char Character::getPlayerOrientation() const
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

void Character::setPlayerMovement(sf::Vector2f &finalPos, const uint &orientation, int freq, int duration)
{
	_duration = duration;
	_freq = freq;
	if (oneTime) {
		_position = _nextPos;
	}
	oneTime = true;
	_totalDist = 0;
	_orientation = static_cast<char>(orientation);
	_nextPos = finalPos;
	_action = true;
}

bool Character::getAction() const
{
	return _action;
}

void Character::setPlayerTake(int freq, int duration)
{
	_duration = duration;
	_freq = freq;
	if (_nextPos.x != 0 && _nextPos.y != 0)
		_position = _nextPos;
	_actualSprite = 0;
	_totalDist = 0;

	_orientation = TAKE;
	_action = true;
}

const sf::Vector2f &Character::getPlayerPosition() const
{
	return _position;
}

void Character::setPlayerIncant(int freq, int duration, sf::Vector2f &newPos)
{
	_duration = duration;
	_freq = freq;
	_position.x = newPos.x * 100;
	_position.y = newPos.y * 100;
	_actualSprite = 0;
	_totalDist = 0;
	_orientation = INCANT;
	_action = true;
}

void Character::setPlayerBroadcast(int freq, int duration)
{
	_duration = duration;
	_freq = freq;
	_orientation = BROADCAST;
	_actualSprite = 0;
	_totalDist = 0;
	_action = true;
}

void Character::checkOutMap()
{
	bool outOfMap = false;
	if (_position.x / 100 > _mapSize.x - 1) {
		_position.x = 0;
		outOfMap = true;
	}
	else if (_position.x / 100 < 0) {
		_position.x = (_mapSize.x - 1) * 100;
		outOfMap = true;
	}

	if (_position.y / 100 > _mapSize.y - 1) {
		_position.y = 0;
		outOfMap = true;
	}
	else if (_position.y / 100 < 0) {
		_position.y = (_mapSize.y - 1) * 100;
		outOfMap = true;
	}
	if (outOfMap) {
		_action = false;
		_totalDist = 0;
	}
}

void Character::levelUp()
{
	_level++;
}

void Character::setEgg()
{
	_orientation = EGG;
}
