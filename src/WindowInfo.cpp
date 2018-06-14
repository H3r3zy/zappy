//
// Created by wisenoa on 13/06/18.
//


#include <unistd.h>
#include "WindowInfo.hpp"

WindowInfo::WindowInfo()
{
	_font.loadFromFile("arial.ttf");
	_text.setFont(_font);
	_text.setString("FPS:");
	_text.setCharacterSize(30);

	_textEntity.setFont(_font);
	_textEntity.setString("FPS:");
	_textEntity.setCharacterSize(30);

	_clock.restart();
}

sf::Text &WindowInfo::getFPS()
{
	static int fps = 0;
	++fps;
	if (_clock.getElapsedTime().asMilliseconds() >= 1000) {
		_text.setString("FPS: " + std::to_string(fps));
		sf::Time frameTime = _clock.restart();
		fps = 0;
	}
	return _text;
}

void WindowInfo::drawInfo(sf::RenderWindow &window)
{
	window.draw(getFPS());
	window.draw(_textEntity);
}

void WindowInfo::updateInfo(uint nbEntity, sf::View &camera)
{
	std::cout << nbEntity << std::endl;
	_text.setPosition(camera.getCenter().x - (camera.getSize().x / 2), camera.getCenter().y - (camera.getSize().y / 2));
	_textEntity.setPosition(camera.getCenter().x - (camera.getSize().x / 2), camera.getCenter().y - (camera.getSize().y / 2) + 40);
	_textEntity.setString("Nb. Entity :" + std::to_string(nbEntity));
}
