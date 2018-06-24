//
// EPITECH PROJECT, 2018
// Water.hpp
// File description:
// Water
//

#ifndef CLIENT_WATER_HPP
#define CLIENT_WATER_HPP

#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>
#include "AMotionShape.hpp"

class Water : public AMotionShape {
	typedef std::chrono::time_point<std::chrono::system_clock> chrono_t;
	public:
	Water(sf::Vector2f &position, std::vector<sf::Texture> &texturePack);
	~Water() = default;

	 sf::Sprite getSprite();

	private:
	chrono_t _beginTime;
};

#endif //CLIENT_WATER_HPP
