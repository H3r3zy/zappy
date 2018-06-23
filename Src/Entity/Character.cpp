//
// Created by wisenoa on 15/06/18.
//

#include <SFML/Graphics/RenderWindow.hpp>
#include "Character.hpp"
#include <unistd.h>

Character::Character(std::map<char, std::vector<sf::Texture>> &_texturePack, sf::Vector2f &position, uint id, int freq) : AMotionShape(position), _id(id), _freq(freq)
{
	 _beginTime = std::chrono::system_clock::now();
	for (int i = 0; i < _texturePack[WALK_LEFT].size(); i++) {
		_sprite[WALK_LEFT].emplace_back(sf::Sprite());
		_sprite[WALK_RIGHT].emplace_back(sf::Sprite());
		_sprite[WALK_UP].emplace_back(sf::Sprite());
		_sprite[WALK_DOWN].emplace_back(sf::Sprite());
		_sprite[TAKE].emplace_back(sf::Sprite());
	}
	for (int i = 0; i < 9; i++) {
		_sprite[WALK_LEFT][i].setTexture(_texturePack[WALK_LEFT][i]);
		_sprite[WALK_RIGHT][i].setTexture(_texturePack[WALK_RIGHT][i]);
		_sprite[WALK_UP][i].setTexture(_texturePack[WALK_UP][i]);
		_sprite[WALK_DOWN][i].setTexture(_texturePack[WALK_DOWN][i]);
		_sprite[TAKE][i].setTexture(_texturePack[TAKE][i]);
	}
	usleep(100);
	srand(time(NULL));
//	_sprite[WALK_LEFT][0]->setTexture(_texturePack[WALK_LEFT][0]);
}

Character::~Character()
{
}

sf::Sprite &Character::getCharacter()
{
	// 0 => 100 => 7 sec
	//_freq = 100;
	if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - _beginTime).count() > (100 / _freq)) {
	//	//std::cout << "il c passé une dixieme de seconde" << std::endl;

		double savetime = (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - _beginTime).count()) / 7;

		// TODO A DEGAGER
		if (_action) {
			//std::cout << "il c passé " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - _beginTime).count() << "millisecondes (normal = 10)" <<std::endl;
			//printf("avant le calucl, savetime vaut %f  \n", savetime);

			savetime *= _freq;
			savetime /= 10;
			//printf("je suis supposé avancer de %f pixels \n", savetime);

			//std::cout << "Le joueur " << _id << " est en action" << std::endl;
			//double dist = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - _beginTime).count() * (500 / 7);
			if (_orientation == WALK_LEFT)
				_position.x -= savetime;
			else if (_orientation == WALK_RIGHT)
				_position.x += savetime;
			else if (_orientation == WALK_UP)
				_position.y -= savetime;
			else if (_orientation == WALK_DOWN)
				_position.y += savetime;

			_actualSprite++;
			if (_actualSprite == 8)
				_actualSprite = 0;


			_testTmp++;


			_totalDist += savetime;
			//std::cout << "j'ai parcourur une distance total de " << _totalDist << std::endl;
			//std::cout << " le tmp = " << _testTmp << std::endl;
			if (_totalDist >= 100) {
				_action = false;
				_testTmp = 0;
				_totalDist = 0;
			}
			//std::cout << "je veux le mettre en pos" << _position.x << " " << _position.y << " et son orientation ";
			//printf("%d\n", _orientation);


		}
		if (savetime != 0)
			_beginTime = std::chrono::system_clock::now();
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
	_totalDist = 0;
	_actualSprite = 0;

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

void Character::setPlayerMovement(sf::Vector2f &finalPos, const uint &orientation, int freq)
{
	_freq = freq;
	if (oneTime) {
		_position = _nextPos;
		//std::cout << "nextpos = " << _nextPos.x << " " << _nextPos.y << std::endl;
	}
	oneTime = true;
	_testTmp = 0;
	_totalDist = 0;
	_orientation = static_cast<char>(orientation);
	_nextPos = finalPos;
	_action = true;
}

const bool Character::getAction() const
{
	return _action;
}

void Character::setPlayerTake(char orientation, uint resourceNumber)
{
	if (_nextPos.x != 0 && _nextPos.y != 0)
		_position = _nextPos;
	_actualSprite = 0;
	_testTmp = 0;
	_totalDist = 0;

	_orientation = TAKE;
	_action = true;
}

const sf::Vector2f &Character::getPlayerPosition() const
{
	return _position;
}
