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
#include <Entity/AMotionShape.hpp>

class Character : public AMotionShape {
	typedef std::chrono::time_point<std::chrono::system_clock> chrono_t;
	enum {
		WALK_DOWN,
		WALK_UP,
		WALK_LEFT,
		WALK_RIGHT
	};
	public:
	Character(std::map<char, std::vector<sf::Texture>> &_texturePack, sf::Vector2f &position);
	static bool playerLoop(sf::RenderWindow &window);

	sf::Sprite &getCharacter();

	~Character();

	private:
	chrono_t _beginTime;
	char _action;


	// TODO LE DEGAGER
	int _testTmp = 0;
	int _randomDirection = 2;
	bool oneTime = true;


};

#endif //PSU_ZAPPY_2017_CHARACTER_HPP
