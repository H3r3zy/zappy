/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <iostream>
#include <chrono>
#include "TextInput.hpp"

irc::TextInput::TextInput(const std::string &pathFont, sf::IntRect pos)
	: AbstractObjectSFML(pos), _index(0)
{
	this->_block = true;
	if (this->_font.loadFromFile(pathFont)) {
		this->_text = sf::Text("", this->_font);
		this->_text.setCharacterSize(this->_pos.height);
		this->_text.setFillColor(sf::Color::White);
		this->_text.setPosition(this->_pos.left, this->_pos.top);
	} else {
		throw std::exception();
	}
}

void irc::TextInput::leftKey(void)
{
	if (this->_index > 0) {
		this->_index--;
	}
}

void irc::TextInput::rightKey(void)
{
	if ((unsigned int)this->_index < this->_prompt.length()) {
		this->_index++;
	}
}

void irc::TextInput::deleteKey(void)
{
	this->_prompt.erase(this->_index, 1);
}

void irc::TextInput::backspaceKey(void)
{
	if (this->_index > 0) {
		this->_prompt.erase(this->_index - 1, 1);
		this->_index--;
	}
}

void irc::TextInput::textKey(sf::Event event)
{
	if (event.type == sf::Event::TextEntered && event.text.unicode < 128 && event.text.unicode > 31) {
		this->_prompt.insert(this->_index, 1, event.text.unicode);
		this->_index++;
	}
}

void irc::TextInput::updateString(sf::Event event)
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		this->leftKey();
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		this->rightKey();
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) && event.text.unicode == 8)
		this->backspaceKey();
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Delete) && event.text.unicode == 127)
		this->deleteKey();
	else
		this->textKey(event);
}

bool irc::TextInput::updateEvent(sf::Event &event, sf::RenderWindow &window, sf::Vector2f &windowSize)
{
	bool check = false;

	if (!this->_isUsed)
		return false;
	managePosMouse(event, window, windowSize);
	manageScroll(event);
	for (auto it = this->_keyBinding.begin() ; it != this->_keyBinding.end() ; ++it) {
		if (event.type == sf::Event::KeyPressed && event.key.code == it->first)
			it->second();
		if (sf::Keyboard::isKeyPressed(it->first))
			check = true;
	}
	if (this->_block)
		return false;
	if (!check)
		updateString(event);
	return false;
}

void irc::TextInput::clearPrompt(void)
{
	this->_prompt.clear();
	this->_index = 0;
}

void irc::TextInput::setPrompt(std::string newPrompt)
{
	this->clearPrompt();
	this->_prompt = newPrompt;
	this->_index = this->_prompt.length();
}

std::string irc::TextInput::getPrompt() const
{
	return this->_prompt;
}

void irc::TextInput::initStringThenDraw(std::string &result)
{
	static auto begin = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

	if (this->_block || !this->_isUsed) {
		this->_text.setString(result);
		return;
	}
	auto end = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

	int ms = end - begin;
	if (ms % 1400 > 700)
		result.insert(this->_index, "|");
	else
		result.insert(this->_index, " ");
	this->_text.setString(result);
}

bool irc::TextInput::drawObject(sf::RenderWindow &window)
{
	static std::string last_string = "";
	std::string result = this->_prompt;

	initStringThenDraw(result);
	if (last_string != result) {
		sf::FloatRect tmp;
		bool check = false;
		std::size_t i = (std::size_t)this->_index;
		do {
			if (check) {
				if (result.length() / 2 <= i) {
					result.erase(0, 1);
					i--;
				} else
					result.pop_back();
			}
			tmp = this->_text.getLocalBounds();
			this->_text.setString(result);
			check = true;
		} while (tmp.width > this->_pos.width);
		last_string = result;
	}
	window.draw(this->_text);
	return false;
}

void irc::TextInput::setColor(sf::Color color)
{
	this->_text.setFillColor(color);
}

void irc::TextInput::setPos(sf::IntRect pos)
{
	this->_pos = pos;
	this->_text.setPosition(this->_pos.left, this->_pos.top);
	this->_text.setCharacterSize(this->_pos.height);
}

bool irc::TextInput::getBlockPrompt() const
{
	return this->_block;
}

void irc::TextInput::setBlockPrompt(bool block)
{
	this->_block = block;
}