/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <iostream>
#include <chrono>
#include "AbsractObjectSFML.hpp"

irc::AbstractObjectSFML::AbstractObjectSFML(sf::IntRect pos) : irc::IObjectSFML(), _pos(pos), _scrollUsed(false)
{
	this->_funcMouseEvent.insert({irc::MouseEvent::CLICK, nullptr});
	this->_funcMouseEvent.insert({irc::MouseEvent::CLICKOUT, nullptr});
	this->_funcMouseEvent.insert({irc::MouseEvent::HOVER, nullptr});
	this->_funcMouseEvent.insert({irc::MouseEvent::HOVEROUT, nullptr});
	this->_funcMouseEvent.insert({irc::MouseEvent::SCROLLUP, nullptr});
	this->_funcMouseEvent.insert({irc::MouseEvent::SCROLLDOWN, nullptr});
	this->_isUsed = true;
	this->_layer = 1;
	_limitScroll.x = _pos.top;
	_limitScroll.y = _pos.top;
}

void irc::AbstractObjectSFML::managePosMouse(sf::Event &event, sf::RenderWindow &window, sf::Vector2f &windowSize)
{
	sf::Vector2i tmp = sf::Mouse::getPosition(window);
	sf::Vector2f position = {(float)tmp.x / window.getSize().x * windowSize.x, (float)tmp.y / window.getSize().y * windowSize.y};

	if (position.x >= this->_pos.left && position.x <= this->_pos.left + this->_pos.width &&
		position.y >= this->_pos.top && position.y <= this->_pos.top + this->_pos.height) {
		if (_funcMouseEvent[CLICK] && event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
			_funcMouseEvent[CLICK]();
		else if (_funcMouseEvent[HOVER])
			_funcMouseEvent[HOVER]();
	} else if (_funcMouseEvent[CLICKOUT] && event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
		_funcMouseEvent[CLICKOUT]();
	else if (_funcMouseEvent[HOVEROUT])
		_funcMouseEvent[HOVEROUT]();
}

void irc::AbstractObjectSFML::manageKeyBinding(sf::Event &event)
{
	for (auto it = this->_keyBinding.begin() ; it != this->_keyBinding.end() ; ++it) {
		if (event.type == sf::Event::KeyPressed && event.key.code == it->first)
			it->second();
	}
}

void irc::AbstractObjectSFML::manageScroll(sf::Event &event)
{
	int dist = 50;
	auto tmp = getPos();

	if (event.type != sf::Event::MouseWheelMoved || !this->_scrollUsed)
		return;
	if (event.mouseWheel.delta == 1 && _limitScroll.x < tmp.top) {
		tmp.top -= dist;
		if (tmp.top < _limitScroll.x)
			tmp.top = _limitScroll.x;
		setPos(tmp);
		if (_funcMouseEvent[SCROLLUP] != nullptr)
			_funcMouseEvent[SCROLLUP]();
	} else if (event.mouseWheel.delta == -1 && _limitScroll.y > tmp.top) {
		tmp.top += dist;
		if (tmp.top > _limitScroll.y)
			tmp.top = _limitScroll.y;
		setPos(tmp);
		if (_funcMouseEvent[SCROLLDOWN] != nullptr)
			_funcMouseEvent[SCROLLDOWN]();
	}
}

bool irc::AbstractObjectSFML::updateEvent(sf::Event &event, sf::RenderWindow &window, sf::Vector2f &windowSize)
{
	if (!this->_isUsed)
		return false;
	managePosMouse(event, window, windowSize);
	manageScroll(event);
	manageKeyBinding(event);
	return false;
}

void irc::AbstractObjectSFML::setBoolUsed(bool used)
{
	this->_isUsed = used;
}

bool irc::AbstractObjectSFML::getBoolUsed() const
{
	return this->_isUsed;
}

void irc::AbstractObjectSFML::setScrollUsed(bool opt)
{
	this->_scrollUsed = opt;
}

std::size_t irc::AbstractObjectSFML::getLayer() const
{
	return this->_layer;
}

void irc::AbstractObjectSFML::setLayer(std::size_t layer)
{
	if (layer > 1000)
		throw std::exception();
	this->_layer = layer;
}

sf::IntRect irc::AbstractObjectSFML::getPos() const
{
	return this->_pos;
}

void irc::AbstractObjectSFML::setScrollLimitDown(int max)
{
	_limitScroll.y = max;
}

void irc::AbstractObjectSFML::setScrollLimitTop(int max)
{
	_limitScroll.x = max;
}

bool irc::AbstractObjectSFML::getBoolDisplay() const
{
	return _display;
}

void irc::AbstractObjectSFML::setBoolDisplay(bool display)
{
	_display = display;
}