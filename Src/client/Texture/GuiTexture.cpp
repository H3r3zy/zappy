/*
** EPITECH PROJECT, 2018
** client
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <regex>
#include <iostream>
#include <Class/Communication.hpp>
#include <chrono>
#include "ManageServer.hpp"
#include "Gui.hpp"
#include "TextInputBckPlaceHolder.hpp"
#include "GuiTexture.hpp"

zap::GuiTexture::GuiTexture(zap::Gui &base) : _base(base)
{
}

void zap::GuiTexture::initTexture()
{
	initBck();
	initUser();
	initSettingsGame();
	initDataServer();
	initDataGame();
	initSounds();

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
		_user_connected->setText("Connected user: "+ std::to_string(_base._comm._server.user));
		_actual_frequency->setText("Actual frequency: "+ std::to_string(_base._comm.getFreq()));
	});
	_base._monitor->addFuncLoop(0, &zap::GuiTexture::updateServerData, this);
}

void zap::GuiTexture::updateServerData()
{
	static auto begin = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

	auto end = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

	int ms = end - begin;
	if (ms > 700) {
		begin = end;
		_base._comm.writeOnServer("nbu");
		_base._comm.writeOnServer("nbt");

	}
	_base._comm.lockGui();
	auto list_msg = _base._comm.getEnqueueGui();

	for (auto &&it : list_msg) {
		if (it.getCommandName() == "nbt")
			_base._comm._server.team_number = it.getCommand()[0];
		else if (it.getCommandName() == "nbu")
			_base._comm._server.user = it.getCommand()[0];
		else if (it.getCommandName() == "eht" || it.getCommandName() == "edi")
			_base._comm._server.eggs--;
		else if (it.getCommandName() == "bfk")
			_base._comm._server.eggs++;
	}
	_base._comm.getEnqueueGui().clear();
	_base._comm.unlockGui();

}

void zap::GuiTexture::initSounds()
{
	auto container = new zap::Container(sf::IntRect(10, 10, 30, 30));

	zap::Sprite *sounds = new zap::Sprite("extra/gui/sounds.png", sf::IntRect(0, 0, 30, 30));
	zap::Sprite *sounds_off = new zap::Sprite("extra/gui/sounds_off.png", sf::IntRect(0, 0, 30, 30));
	zap::Square *hit_box = new zap::Square(sf::IntRect(10, 10, 30, 30));

	if (_base._music.getStatus() == sf::SoundSource::Stopped)
		sounds->setBoolDisplay(false);
	else
		sounds_off->setBoolDisplay(false);

	container->addObjectList("sounds_off", sounds_off, 5);
	container->addObjectList("sounds", sounds, 5);

	hit_box->addFuncMouseEvent(zap::MouseEvent::CLICK, [this, sounds, sounds_off] {
		if (!sounds->getBoolDisplay()) {
			_base._music.play();
			sounds->setBoolDisplay(true);
			sounds_off->setBoolDisplay(false);
		} else {
			_base._music.pause();
			sounds->setBoolDisplay(false);
			sounds_off->setBoolDisplay(true);
		}
	});


	_base._monitor->addObjectToDraw("sounds_settings", container, 0, 2);
	_base._monitor->addObjectToDraw("hit_box_sounds", hit_box, 0, 0);
}

void zap::GuiTexture::initDataGame()
{
	auto container = new zap::Container(sf::IntRect(10, 495, WIDTH - 10, HEIGHT - 495));
	container->setBoolUsed(false);

	auto title = new zap::Text("extra/Gobold.otf", sf::IntRect(0, 0, 100, 20), "Game Data:");
	title->setColor(sf::Color::Black);
	container->addObjectList("title", title);

	container->addObjectList("egg", new zap::Sprite("extra/gui/egg.png", sf::IntRect(0, 40, 40, 50)));
	_nb_egg = new zap::Text("extra/arial.ttf", sf::IntRect(60, 55, 80, 20), "x ???");
	_nb_egg->setColor(sf::Color::Black);
	container->addObjectList("egg_nb", _nb_egg);

	container->addObjectList("q0", new zap::Sprite("extra/gui/baie.png", sf::IntRect(0, 100, 50, 50)));
	_nb_q0 = new zap::Text("extra/arial.ttf", sf::IntRect(60, 115, 80, 20), "x ???");
	_nb_q0->setColor(sf::Color::Black);
	container->addObjectList("q0_nb", _nb_q0);

	container->addObjectList("q1", new zap::Sprite("extra/gui/list_pokeballs.png", sf::IntRect(0, 160, 50, 50), sf::IntRect(0, 0, 60, 60)));
	_nb_q1 = new zap::Text("extra/arial.ttf", sf::IntRect(60, 175, 80, 20), "x ???");
	_nb_q1->setColor(sf::Color::Black);
	container->addObjectList("q1_nb", _nb_q1);

	container->addObjectList("q2", new zap::Sprite("extra/gui/list_pokeballs.png", sf::IntRect(0, 220, 50, 50), sf::IntRect(60, 0, 60, 60)));
	_nb_q2 = new zap::Text("extra/arial.ttf", sf::IntRect(60, 235, 80, 20), "x ???");
	_nb_q2->setColor(sf::Color::Black);
	container->addObjectList("q2_nb", _nb_q2);

	container->addObjectList("q3", new zap::Sprite("extra/gui/list_pokeballs.png", sf::IntRect(150, 40, 50, 50), sf::IntRect(120, 0, 60, 60)));
	_nb_q3 = new zap::Text("extra/arial.ttf", sf::IntRect(210, 55, 80, 20), "x ???");
	_nb_q3->setColor(sf::Color::Black);
	container->addObjectList("q3_nb", _nb_q3);

	container->addObjectList("q4", new zap::Sprite("extra/gui/list_pokeballs.png", sf::IntRect(150, 100, 50, 50), sf::IntRect(180, 0, 60, 60)));
	_nb_q4 = new zap::Text("extra/arial.ttf", sf::IntRect(210, 115, 80, 20), "x ???");
	_nb_q4->setColor(sf::Color::Black);
	container->addObjectList("q4_nb", _nb_q4);

	container->addObjectList("q5", new zap::Sprite("extra/gui/list_pokeballs.png", sf::IntRect(150, 160, 50, 50), sf::IntRect(180, 120, 60, 60)));
	_nb_q5 = new zap::Text("extra/arial.ttf", sf::IntRect(210, 175, 80, 20), "x ???");
	_nb_q5->setColor(sf::Color::Black);
	container->addObjectList("q5_nb", _nb_q5);

	container->addObjectList("q6", new zap::Sprite("extra/gui/list_pokeballs.png", sf::IntRect(150, 220, 50, 50), sf::IntRect(240, 180, 60, 60)));
	_nb_q6 = new zap::Text("extra/arial.ttf", sf::IntRect(210, 235, 80, 20), "x ???");
	_nb_q6->setColor(sf::Color::Black);
	container->addObjectList("q6_nb", _nb_q6);

	_base._monitor->addObjectToDraw("data_games", container);
}

void zap::GuiTexture::initDataServer()
{
	auto container = new zap::Container(sf::IntRect(10, 350, WIDTH - 10, 100));
	container->setBoolUsed(false);

	auto title = new zap::Text("extra/Gobold.otf", sf::IntRect(0, 0, 100, 20), "Server Data:");
	title->setColor(sf::Color::Black);
	container->addObjectList("title", title);

	auto ip = new zap::Text("extra/arial.ttf", sf::IntRect(0, 25, 100, 20), "IP: " + _ip);
	ip->setColor(sf::Color::Black);
	container->addObjectList("ip", ip);

	_user_connected = new zap::Text("extra/arial.ttf", sf::IntRect(0, 50, 100, 20), "Connected user: ???");
	_user_connected->setColor(sf::Color::Black);
	container->addObjectList("user_connected", _user_connected);

	_nb_teams = new zap::Text("extra/arial.ttf", sf::IntRect(0, 75, 100, 20), "Number of teams: ???");
	_nb_teams->setColor(sf::Color::Black);
	container->addObjectList("nb_teams", _nb_teams);

	_actual_frequency = new zap::Text("extra/arial.ttf", sf::IntRect(0, 100, 100, 20), "Actual frequency: ???");
	_actual_frequency->setColor(sf::Color::Black);
	container->addObjectList("actual_frequency", _actual_frequency);

	_base._monitor->addObjectToDraw("data_server", container);
}

void zap::GuiTexture::initSettingsGame()
{
	auto container = new zap::Container(sf::IntRect(10, 260, WIDTH - 10, 60));
	auto input = zap::TextInputBckPlaceHorder::createInput(sf::IntRect(0, 30, 220, 30), "Frequency", "extra/arial.ttf", 20);
	auto title_change_freq = new zap::Text("extra/Gobold.otf", sf::IntRect(0, 0, 100, 20), "Change frequency:");
	title_change_freq->setColor(sf::Color::Black);

	container->addObjectList("title_change_freq", title_change_freq);
	container->addObjectList("freq", input);

	auto btn = new zap::Sprite("extra/gui/check_hover.png", sf::IntRect(230, 30, 30, 30));
	auto btn_hover = new zap::Sprite("extra/gui/check.png", sf::IntRect(230, 30, 30, 30));

	btn->addFuncMouseEvent(zap::MouseEvent::HOVER, &zap::Sprite::setLayer, btn_hover, 3);
	btn->addFuncMouseEvent(zap::MouseEvent::HOVEROUT, &zap::Sprite::setLayer, btn_hover, 0);

	auto setFreq = [this, input]{
		std::string freq = dynamic_cast<zap::TextInput *>(input->getObjectByName("input"))->getPrompt();
		if (!std::regex_match(freq, std::regex("\\d+")) || std::stoi(freq) <= 0 || std::stoi(freq) >= 200) {
			input->getObjectByName("bck")->setColor(sf::Color(222, 170, 170));
			return;
		}
		_base._comm.setFreq(std::stoi(freq));
		input->getObjectByName("bck")->setColor(sf::Color::White);
		_base._comm.writeOnServer("sst " + freq);
	};
	btn->addFuncMouseEvent(zap::MouseEvent::CLICK, setFreq);
	btn->addFuncKeyEvent(sf::Keyboard::Return, setFreq);

	container->addObjectList("btn", btn, 1);
	container->addObjectList("btn_hover", btn_hover, 0);

	_base._monitor->addObjectToDraw("settings_game", container);
}

void zap::GuiTexture::initUser()
{
	auto container = new zap::Container(sf::IntRect(0, 0, WIDTH, 235));
	container->setBoolUsed(false);
	auto user = new zap::Sprite("extra/gui/user.png", sf::IntRect(70, 20, 160, 160));
	auto nick = new zap::Text("extra/arial.ttf", sf::IntRect(145 - (int)(_nick.size() / 2 * 13), 180, (int)(_nick.size() / 2 * 13), 26), _nick);
	auto sep = new zap::Sprite("extra/gui/separator.png", sf::IntRect(0, 220, WIDTH, 15));
	nick->setColor(sf::Color(50, 50, 50));

	container->addObjectList("user_picture", user);
	container->addObjectList("user_nick", nick);
	container->addObjectList("user_sep", sep);
	_base._monitor->addObjectToDraw("user_header", container);
}

void zap::GuiTexture::initBck()
{
	auto bck = new zap::Square(sf::IntRect(0, 0, WIDTH, HEIGHT));
	bck->setColor(sf::Color(240, 240, 240, 255));
	_base._monitor->addObjectToDraw("background", bck);
}
