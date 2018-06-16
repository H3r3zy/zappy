//
// Created by wisenoa on 15/06/18.
//


#ifndef PSU_ZAPPY_2017_CHARACTER_HPP
#define PSU_ZAPPY_2017_CHARACTER_HPP

#include <iostream>
#include <map>
#include <chrono>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Character {
	typedef std::chrono::time_point<std::chrono::system_clock> chrono_t;
	enum {
		WALK_DOWN,
		WALK_UP,
		WALK_LEFT,
		WALK_RIGHT
	};
	public:
	Character(std::map<char, std::vector<sf::Texture>> &_texturePack, sf::Vector2f &position);
	void setPosition(sf::Vector2f &position);
	void setPosition(float x, float y);
	static bool playerLoop(sf::RenderWindow &window);
	const sf::Vector2f &getPosition() const;

	sf::Sprite &getCharacter();
	~Character();

	private:
	std::map<char, std::vector<sf::Sprite>> _sprite;
	chrono_t _beginTime;
	uint _actualSprite;
	sf::Vector2f _position;
	char _action;


	// TODO LE DEGAGER
	int _testTmp = 0;
	int _randomDirection = 2;
};

#endif //PSU_ZAPPY_2017_CHARACTER_HPP
