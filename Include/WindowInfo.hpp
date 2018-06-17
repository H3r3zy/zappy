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
	enum {
		FPS,
		ENTITY,
		ZOOM
	};
	public:
	WindowInfo();
	~WindowInfo() = default;

	void updateInfo(uint nbEntity, sf::View &camera);
	void updateZoom(float zoom);
	void drawInfo(sf::RenderWindow &window);
	sf::Text &getFPS();

	private:
	sf::Font _font;
	std::vector<sf::Text> _text;
	sf::Clock _clock;
	float _zoom;
};

#endif //PSU_ZAPPY_2017_WINDOWINFO_HPP
