//
// Created by wisenoa on 13/06/18.
//


#include <unistd.h>
#include "WindowInfo.hpp"

WindowInfo::WindowInfo() : _zoom(1)
{
	_text.emplace_back(sf::Text());	_text.emplace_back(sf::Text());	_text.emplace_back(sf::Text());

	_text[FPS].setFont(SfmlTool::getArialFont());
	_text[FPS].setString("FPS:");
	_text[FPS].setCharacterSize(30);

	_text[ENTITY].setFont(SfmlTool::getArialFont());
	_text[ENTITY].setString("Nb. Entity :");
	_text[ENTITY].setCharacterSize(30);

	_text[ZOOM].setFont(SfmlTool::getArialFont());
	_text[ZOOM].setString("Zoom x1");
	_text[ZOOM].setCharacterSize(30);

	_clock.restart();
}

sf::Text &WindowInfo::getFPS()
{
	static int fps = 0;
	++fps;
	if (_clock.getElapsedTime().asMilliseconds() >= 1000) {
		_text[FPS].setString("FPS: " + std::to_string(fps));
		sf::Time frameTime = _clock.restart();
		fps = 0;
	}
	return _text[FPS];
}

void WindowInfo::drawInfo(sf::RenderWindow &window)
{
	window.draw(getFPS());
	window.draw(_text[ENTITY]);
	window.draw(_text[ZOOM]);
}

void WindowInfo::updateInfo(uint nbEntity, sf::View &camera)
{
	_text[FPS].setPosition(camera.getCenter().x - (camera.getSize().x / 2), camera.getCenter().y - (camera.getSize().y / 2));
	_text[ENTITY].setPosition(camera.getCenter().x - (camera.getSize().x / 2), camera.getCenter().y - (camera.getSize().y / 2) + 40);
	_text[ZOOM].setPosition(camera.getCenter().x - (camera.getSize().x / 2), camera.getCenter().y - (camera.getSize().y / 2) + 80);
	_text[ENTITY].setString("Nb. Entity :" + std::to_string(nbEntity));
}

void WindowInfo::updateZoom(float zoom)
{
	_zoom /= zoom;
	_text[ZOOM].setString("Zoom x" + std::to_string(_zoom));
}

