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
	enum {
		WALK_DOWN,
		WALK_UP,
		WALK_LEFT,
		WALK_REIGHT
	};
	public:
	Character(std::map<char, std::vector<sf::Texture>> &_texturePack);
	static bool playerLoop(sf::RenderWindow &window);

	sf::Sprite &getCharacter();
	~Character();

	private:
	std::map<char, std::vector<sf::Sprite>> _sprite;
	uint _actualSprite;
	sf::Vector2f _position;
	char _action;
};

#endif //PSU_ZAPPY_2017_CHARACTER_HPP
