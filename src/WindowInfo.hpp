//
// Created by wisenoa on 13/06/18.
//


#ifndef PSU_ZAPPY_2017_WINDOWINFO_HPP
#define PSU_ZAPPY_2017_WINDOWINFO_HPP

#include <iostream>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

class WindowInfo {
	public:
	WindowInfo();
	~WindowInfo() = default;

	sf::Text &getFPS(sf::View &camera);

	private:
	sf::Font _font;
	sf::Text _text;
	sf::Clock _clock;
};

#endif //PSU_ZAPPY_2017_WINDOWINFO_HPP
