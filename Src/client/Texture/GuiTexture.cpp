/*
** EPITECH PROJECT, 2018
** client
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <regex>
#include <iostream>
#include <Class/Communication.hpp>
#include "ManageServer.hpp"
#include "Gui.hpp"
#include "TextInputBckPlaceHolder.hpp"
#include "GuiTexture.hpp"

irc::GuiTexture::GuiTexture(irc::Gui &base) : _base(base)
{
}

void irc::GuiTexture::initTexture()
{
	initBck();
	initUser();
	initSettingsGame();
	initDataServer();
	initDataGame();

	_base._monitor->addFuncLoop(0, [this] {
		_nb_egg->setText("x "+ std::to_string(_base._comm._server.eggs));
		_nb_q0->setText("x "+ std::to_string(_base._comm._server.ressources.q0));
		_nb_q1->setText("x "+ std::to_string(_base._comm._server.ressources.q1));
		_nb_q2->setText("x "+ std::to_string(_base._comm._server.ressources.q2));
		_nb_q3->setText("x "+ std::to_string(_base._comm._server.ressources.q3));
		_nb_q4->setText("x "+ std::to_string(_base._comm._server.ressources.q4));
		_nb_q5->setText("x "+ std::to_string(_base._comm._server.ressources.q5));
		_nb_q6->setText("x "+ std::to_string(_base._comm._server.ressources.q6));
		_nb_teams->setText("Number of teams: "+ std::to_string(_base._comm._server.team_number));
		_user_connected->setText("User connected: "+ std::to_string(_base._comm._server.user));
	});
	_base._monitor->addFuncLoop(0, &irc::GuiTexture::updateServerData, this);
}

void irc::GuiTexture::updateServerData()
{
//	_base._comm.writeOnServer("nbu");
//	_base._comm.writeOnServer("nbt");
	_base._comm.lockGui();
	auto list_msg = _base._comm.getEnqueueGui();

	for (auto &&it : list_msg) {
		if (it.getCommandName() == "nbt") {
			_base._comm._server.team_number = it.getCommand()[0];
		}
		if (it.getCommandName() == "nbu") {
			_base._comm._server.user = it.getCommand()[0];
		}
	}
	_base._comm.getEnqueueGui().clear();
	_base._comm.unlockGui();

}

void irc::GuiTexture::initDataGame()
{
	auto container = new irc::Container(sf::IntRect(10, 480, WIDTH - 10, HEIGHT - 480));
	container->setBoolUsed(false);

	auto title = new irc::Text("extra/Gobold.otf", sf::IntRect(0, 0, 100, 20), "Data Games:");
	title->setColor(sf::Color::Black);
	container->addObjectList("title", title);

	container->addObjectList("egg", new irc::Sprite("extra/gui/egg.png", sf::IntRect(0, 40, 40, 50)));
	_nb_egg = new irc::Text("extra/arial.ttf", sf::IntRect(60, 55, 80, 20), "x ???");
	_nb_egg->setColor(sf::Color::Black);
	container->addObjectList("egg_nb", _nb_egg);

	container->addObjectList("q0", new irc::Sprite("extra/gui/baie.png", sf::IntRect(0, 100, 50, 50)));
	_nb_q0 = new irc::Text("extra/arial.ttf", sf::IntRect(60, 115, 80, 20), "x ???");
	_nb_q0->setColor(sf::Color::Black);
	container->addObjectList("q0_nb", _nb_q0);

	container->addObjectList("q1", new irc::Sprite("extra/gui/list_pokeballs.png", sf::IntRect(0, 160, 50, 50), sf::IntRect(0, 0, 60, 60)));
	_nb_q1 = new irc::Text("extra/arial.ttf", sf::IntRect(60, 175, 80, 20), "x ???");
	_nb_q1->setColor(sf::Color::Black);
	container->addObjectList("q1_nb", _nb_q1);

	container->addObjectList("q2", new irc::Sprite("extra/gui/list_pokeballs.png", sf::IntRect(0, 220, 50, 50), sf::IntRect(60, 0, 60, 60)));
	_nb_q2 = new irc::Text("extra/arial.ttf", sf::IntRect(60, 235, 80, 20), "x ???");
	_nb_q2->setColor(sf::Color::Black);
	container->addObjectList("q2_nb", _nb_q2);

	container->addObjectList("q3", new irc::Sprite("extra/gui/list_pokeballs.png", sf::IntRect(150, 40, 50, 50), sf::IntRect(120, 0, 60, 60)));
	_nb_q3 = new irc::Text("extra/arial.ttf", sf::IntRect(210, 55, 80, 20), "x ???");
	_nb_q3->setColor(sf::Color::Black);
	container->addObjectList("q3_nb", _nb_q3);

	container->addObjectList("q4", new irc::Sprite("extra/gui/list_pokeballs.png", sf::IntRect(150, 100, 50, 50), sf::IntRect(180, 0, 60, 60)));
	_nb_q4 = new irc::Text("extra/arial.ttf", sf::IntRect(210, 115, 80, 20), "x ???");
	_nb_q4->setColor(sf::Color::Black);
	container->addObjectList("q4_nb", _nb_q4);

	container->addObjectList("q5", new irc::Sprite("extra/gui/list_pokeballs.png", sf::IntRect(150, 160, 50, 50), sf::IntRect(180, 120, 60, 60)));
	_nb_q5 = new irc::Text("extra/arial.ttf", sf::IntRect(210, 175, 80, 20), "x ???");
	_nb_q5->setColor(sf::Color::Black);
	container->addObjectList("q5_nb", _nb_q5);

	container->addObjectList("q6", new irc::Sprite("extra/gui/list_pokeballs.png", sf::IntRect(150, 220, 50, 50), sf::IntRect(240, 180, 60, 60)));
	_nb_q6 = new irc::Text("extra/arial.ttf", sf::IntRect(210, 235, 80, 20), "x ???");
	_nb_q6->setColor(sf::Color::Black);
	container->addObjectList("q6_nb", _nb_q6);

	_base._monitor->addObjectToDraw("data_games", container);
}

void irc::GuiTexture::initDataServer()
{
	auto container = new irc::Container(sf::IntRect(10, 350, WIDTH - 10, 100));
	container->setBoolUsed(false);

	auto title = new irc::Text("extra/Gobold.otf", sf::IntRect(0, 0, 100, 20), "Data Server:");
	title->setColor(sf::Color::Black);
	container->addObjectList("title", title);

	auto ip = new irc::Text("extra/arial.ttf", sf::IntRect(0, 25, 100, 20), "IP: " + _ip);
	ip->setColor(sf::Color::Black);
	container->addObjectList("ip", ip);

	_user_connected = new irc::Text("extra/arial.ttf", sf::IntRect(0, 50, 100, 20), "User connected: ???");
	_user_connected->setColor(sf::Color::Black);
	container->addObjectList("user_connected", _user_connected);

	_nb_teams = new irc::Text("extra/arial.ttf", sf::IntRect(0, 75, 100, 20), "Number of teams: ???");
	_nb_teams->setColor(sf::Color::Black);
	container->addObjectList("nb_teams", _nb_teams);

	_base._monitor->addObjectToDraw("data_server", container);
}

void irc::GuiTexture::initSettingsGame()
{
	auto container = new irc::Container(sf::IntRect(10, 260, WIDTH - 10, 60));
	auto input = irc::TextInputBckPlaceHorder::createInput(sf::IntRect(0, 30, 220, 30), "Frequency", "extra/arial.ttf", 20);
	auto title_change_freq = new irc::Text("extra/Gobold.otf", sf::IntRect(0, 0, 100, 20), "Change frequency:");
	title_change_freq->setColor(sf::Color::Black);

	container->addObjectList("title_change_freq", title_change_freq);
	container->addObjectList("freq", input);

	auto btn = new irc::Sprite("extra/gui/check_hover.png", sf::IntRect(230, 30, 30, 30));
	auto btn_hover = new irc::Sprite("extra/gui/check.png", sf::IntRect(230, 30, 30, 30));

	btn->addFuncMouseEvent(irc::MouseEvent::HOVER, &irc::Sprite::setLayer, btn_hover, 3);
	btn->addFuncMouseEvent(irc::MouseEvent::HOVEROUT, &irc::Sprite::setLayer, btn_hover, 0);
	btn->addFuncMouseEvent(irc::MouseEvent::CLICK, [this, input]{
		std::string freq = dynamic_cast<irc::TextInput *>(input->getObjectByName("input"))->getPrompt();
		if (!std::regex_match(freq, std::regex("\\d+")) || std::stoi(freq) <= 0) {
			input->getObjectByName("bck")->setColor(sf::Color(222, 170, 170));
			return;
		}
		input->getObjectByName("bck")->setColor(sf::Color::White);
		_base._comm.writeOnServer("sst " + freq);
	});

	container->addObjectList("btn", btn, 1);
	container->addObjectList("btn_hover", btn_hover, 0);

	_base._monitor->addObjectToDraw("settings_game", container);
}

void irc::GuiTexture::initUser()
{
	auto container = new irc::Container(sf::IntRect(0, 0, WIDTH, 235));
	container->setBoolUsed(false);
	auto user = new irc::Sprite("extra/gui/user.png", sf::IntRect(70, 20, 160, 160));
	auto nick = new irc::Text("extra/arial.ttf", sf::IntRect(145 - (int)(_nick.size() / 2 * 13), 180, (int)(_nick.size() / 2 * 13), 26), _nick);
	auto sep = new irc::Sprite("extra/gui/separator.png", sf::IntRect(0, 220, WIDTH, 15));
	nick->setColor(sf::Color(50, 50, 50));

	container->addObjectList("user_picture", user);
	container->addObjectList("user_nick", nick);
	container->addObjectList("user_sep", sep);
	_base._monitor->addObjectToDraw("user_header", container);
}

void irc::GuiTexture::initBck()
{
	auto bck = new irc::Square(sf::IntRect(0, 0, WIDTH, HEIGHT));
	bck->setColor(sf::Color(240, 240, 240, 255));
	_base._monitor->addObjectToDraw("background", bck);
}
