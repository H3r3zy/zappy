//
// EPITECH PROJECT, 2018
// GameTex.hpp
// File description:
// GameText
//

#ifndef PSU_ZAPPY_2017_GAMETEXT_HPP
#define PSU_ZAPPY_2017_GAMETEXT_HPP

#include "AText.hpp"

class GameText : public AText {
	public:
	GameText(const sf::Font &font, sf::Vector2f &position);
	~GameText() = default;

	void setColor(const sf::Color &color);
	void setOutline(const sf::Color &color, float thickness);

	private:
};

#endif //PSU_ZAPPY_2017_GAMETEXT_HPP
