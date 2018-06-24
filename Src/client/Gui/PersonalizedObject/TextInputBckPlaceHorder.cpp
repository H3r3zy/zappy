/*
** EPITECH PROJECT, 2018
** client
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <iostream>
#include "TextInputBckPlaceHolder.hpp"

zap::Container *zap::TextInputBckPlaceHorder::createInput(const sf::IntRect &pos, const std::string &placeholder, const std::string &font, int fontSize)
{
	auto container = new zap::Container(pos);

	zap::Square *bck_input_nick_border = new zap::Square(sf::IntRect(0, 0, pos.width, pos.height));
	bck_input_nick_border->setColor(sf::Color::Black);
	zap::Square *bck_input_nick = new zap::Square(sf::IntRect(2, 2, pos.width - 4, pos.height - 4));

	zap::Text *input_placeholder = new zap::Text(font, sf::IntRect(12, 2, pos.width - 12, fontSize), placeholder);
	input_placeholder->setColor(sf::Color(150, 150, 150));

	zap::TextInput *input = new zap::TextInput(font, sf::IntRect(12, 2, pos.width - 24, fontSize));
	input->setColor(sf::Color::Black);
	input->setBoolUsed(false);

	bck_input_nick_border->addFuncMouseEvent(CLICK, &zap::TextInputBckPlaceHorder::inputTextWrite, input_placeholder, input, 0);
	bck_input_nick_border->addFuncMouseEvent(CLICKOUT, &zap::TextInputBckPlaceHorder::inputTextWrite, input_placeholder, input, 1);


	container->addObjectList("border", bck_input_nick_border, 0);
	container->addObjectList("bck", bck_input_nick, 1);
	container->addObjectList("input", input, 0);
	container->addObjectList("placeholder", input_placeholder, 2);

	return container;
}

void zap::TextInputBckPlaceHorder::inputTextWrite(zap::IObjectSFML *placeholder, zap::IObjectSFML *input_obj, bool layer)
{
	auto input = dynamic_cast<zap::TextInput *>(input_obj);

	if (!layer) {
		input->setLayer(10);
		input->setBlockPrompt(false);
		input->setBoolUsed(true);
		placeholder->setLayer(0);
	} else {
		if (input->getPrompt().empty())
			placeholder->setLayer(10);
		else
			input->setLayer(10);
		input->setBoolUsed(false);
		input->setBlockPrompt(true);
	}
}
