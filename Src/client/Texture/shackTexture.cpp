/*
** EPITECH PROJECT, 2018
** client
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <iostream>
#include <Class/Communication.hpp>
#include "Gui.hpp"
#include "shackTexture.hpp"

irc::shackTexture::shackTexture(irc::Gui &base) : _base(base)
{
}

void irc::shackTexture::initTexture()
{
	initBck();
	initHeader();
	initNbPlayer();
	initData();
	initArrow();
	initClose();

	_base._monitor->addFuncLoop(-1, [this] {
		if (_base._comm._listId.empty()) {
			_base._monitor->setScene(0);
			return;
		}
		_base._monitor->getObjectByName("arrow_change", -1)->setBoolDisplay(_base._comm._listId.size() != 1);
		_nb_q0->setText("x "+ std::to_string(_base._comm._shack.ressources.q0));
		_nb_q1->setText("x "+ std::to_string(_base._comm._shack.ressources.q1));
		_nb_q2->setText("x "+ std::to_string(_base._comm._shack.ressources.q2));
		_nb_q3->setText("x "+ std::to_string(_base._comm._shack.ressources.q3));
		_nb_q4->setText("x "+ std::to_string(_base._comm._shack.ressources.q4));
		_nb_q5->setText("x "+ std::to_string(_base._comm._shack.ressources.q5));
		_nb_q6->setText("x "+ std::to_string(_base._comm._shack.ressources.q6));
		_nb_player->setText(std::to_string(_base._comm._shack.player_on) + " player(s)");

		std::string id = std::to_string(_base._comm._shack._pos.first) + " : " + std::to_string(_base._comm._shack._pos.second);
		_nickShack->setPos(sf::IntRect(145 - (int)(id.size() / 2 * 13), 180, (int)(id.size() / 2 * 13), 26));
		_nickShack->setText(id);

	});
	_base._monitor->addFuncLoop(-1, &irc::shackTexture::updateShack, this);
}

void irc::shackTexture::updateShack()
{
	static auto begin = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

	auto end = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

	int ms = end - begin;
	if (ms > 700) {
		begin = end;
		_base._comm.writeOnServer("bct " + std::to_string(_base._comm._shack._pos.first) + " " + std::to_string(_base._comm._shack._pos.second));
	}

	_base._comm.lockGui();
	auto list_msg = _base._comm.getEnqueueGui();

	for (auto &&it : list_msg) {
		if (it.getCommandName() == "bct" && _base._comm._shack._pos.first == it.getCommand()[0] && _base._comm._shack._pos.second == it.getCommand()[1]) {
			_base._comm._shack.ressources.q0 = it.getCommand()[8];
			_base._comm._shack.ressources.q1 = it.getCommand()[2];
			_base._comm._shack.ressources.q2 = it.getCommand()[3];
			_base._comm._shack.ressources.q3 = it.getCommand()[4];
			_base._comm._shack.ressources.q4 = it.getCommand()[5];
			_base._comm._shack.ressources.q5 = it.getCommand()[6];
			_base._comm._shack.ressources.q6 = it.getCommand()[7];
			break;
		} else if (it.getCommandName() == "eht" || it.getCommandName() == "edi")
			_base._comm._server.eggs--;
		else if (it.getCommandName() == "enw")
			_base._comm._server.eggs++;
	}
	_base._comm.getEnqueueGui().clear();
	_base._comm.unlockGui();
}

void irc::shackTexture::initClose()
{
	auto close = new irc::Sprite("extra/gui/close.png", sf::IntRect(250, 10, 30, 30));

	close->addFuncMouseEvent(irc::MouseEvent::CLICK, [this] {
		if (_base._comm._listId.size() == 1) {
			_base._comm._listId.clear();
			_base._monitor->setScene(0);
			return;
		}
		_base._comm._listId.erase(_base._comm._listId.begin());
		if (_base._comm._listId[0] != -1)
			_base._monitor->setScene(1);
	});
	_base._monitor->addObjectToDraw("close", close, -1, 2);
}

void irc::shackTexture::initArrow()
{
	auto container = new irc::Container(sf::IntRect(10, 0, WIDTH - 10, HEIGHT));

	auto arrow_left = new irc::Sprite("extra/gui/arrow.png", sf::IntRect(0, 100, 50, 40));
	container->addObjectList("arrow_left", arrow_left, 1);
	auto arrow_right = new irc::Sprite("extra/gui/arrow_right.png", sf::IntRect(230, 100, 50, 40));
	container->addObjectList("arrow_right", arrow_right, 1);

	auto arrow_left_hover = new irc::Sprite("extra/gui/arrow_hover.png", sf::IntRect(0, 100, 50, 40));
	container->addObjectList("arrow_left_hover", arrow_left_hover, 0);
	auto arrow_right_hover = new irc::Sprite("extra/gui/arrow_right_hover.png", sf::IntRect(230, 100, 50, 40));
	container->addObjectList("arrow_right_hover", arrow_right_hover, 0);

	arrow_left_hover->addFuncMouseEvent(irc::MouseEvent::HOVER, [arrow_left_hover] {arrow_left_hover->setLayer(12);});
	arrow_left_hover->addFuncMouseEvent(irc::MouseEvent::HOVEROUT, [arrow_left_hover] {arrow_left_hover->setLayer(0);});

	arrow_right_hover->addFuncMouseEvent(irc::MouseEvent::HOVER, [arrow_right_hover] {arrow_right_hover->setLayer(12);});
	arrow_right_hover->addFuncMouseEvent(irc::MouseEvent::HOVEROUT, [arrow_right_hover] {arrow_right_hover->setLayer(0);});

	arrow_left->addFuncMouseEvent(irc::MouseEvent::CLICK, [this] {
		int save = _base._comm._listId[0];
		_base._comm._listId.erase(_base._comm._listId.begin());
		_base._comm._listId.push_back(save);

		if (_base._comm._listId[0] != -1)
			_base._monitor->setScene(1);
	});

	arrow_right->addFuncMouseEvent(irc::MouseEvent::CLICK, [this] {
		int save = _base._comm._listId[_base._comm._listId.size() - 1];
		_base._comm._listId.pop_back();
		_base._comm._listId.insert(_base._comm._listId.begin(), save);

		if (_base._comm._listId[0] != -1)
			_base._monitor->setScene(1);
	});

	_base._monitor->addObjectToDraw("arrow_change", container, -1, 10);
}

void irc::shackTexture::initData()
{
	auto container = new irc::Container(sf::IntRect(10, 380, WIDTH - 10, HEIGHT - 380));
	container->setBoolUsed(false);

	auto title = new irc::Text("extra/Gobold.otf", sf::IntRect(0, 0, 100, 20), "Data Games:");
	title->setColor(sf::Color::Black);
	container->addObjectList("title", title);

	container->addObjectList("q0", new irc::Sprite("extra/gui/baie.png", sf::IntRect(0, 40, 40, 50)));
	_nb_q0 = new irc::Text("extra/arial.ttf", sf::IntRect(60, 55, 80, 20), "x ???");
	_nb_q0->setColor(sf::Color::Black);
	container->addObjectList("q0_nb", _nb_q0);

	container->addObjectList("q1", new irc::Sprite("extra/gui/list_pokeballs.png", sf::IntRect(0, 100, 50, 50), sf::IntRect(0, 0, 60, 60)));
	_nb_q1 = new irc::Text("extra/arial.ttf", sf::IntRect(60, 115, 80, 20), "x ???");
	_nb_q1->setColor(sf::Color::Black);
	container->addObjectList("q1_nb", _nb_q1);

	container->addObjectList("q2", new irc::Sprite("extra/gui/list_pokeballs.png", sf::IntRect(0, 160, 50, 50), sf::IntRect(60, 0, 60, 60)));
	_nb_q2 = new irc::Text("extra/arial.ttf", sf::IntRect(60, 175, 80, 20), "x ???");
	_nb_q2->setColor(sf::Color::Black);
	container->addObjectList("q2_nb", _nb_q2);

	container->addObjectList("q3", new irc::Sprite("extra/gui/list_pokeballs.png", sf::IntRect(0, 220, 50, 50), sf::IntRect(120, 0, 60, 60)));
	_nb_q3 = new irc::Text("extra/arial.ttf", sf::IntRect(60, 235, 80, 20), "x ???");
	_nb_q3->setColor(sf::Color::Black);
	container->addObjectList("q3_nb", _nb_q3);

	container->addObjectList("q4", new irc::Sprite("extra/gui/list_pokeballs.png", sf::IntRect(150, 40, 50, 50), sf::IntRect(180, 0, 60, 60)));
	_nb_q4 = new irc::Text("extra/arial.ttf", sf::IntRect(210, 55, 80, 20), "x ???");
	_nb_q4->setColor(sf::Color::Black);
	container->addObjectList("q4_nb", _nb_q4);

	container->addObjectList("q5", new irc::Sprite("extra/gui/list_pokeballs.png", sf::IntRect(150, 100, 50, 50), sf::IntRect(180, 120, 60, 60)));
	_nb_q5 = new irc::Text("extra/arial.ttf", sf::IntRect(210, 115, 80, 20), "x ???");
	_nb_q5->setColor(sf::Color::Black);
	container->addObjectList("q5_nb", _nb_q5);

	container->addObjectList("q6", new irc::Sprite("extra/gui/list_pokeballs.png", sf::IntRect(150, 160, 50, 50), sf::IntRect(240, 180, 60, 60)));
	_nb_q6 = new irc::Text("extra/arial.ttf", sf::IntRect(210, 175, 80, 20), "x ???");
	_nb_q6->setColor(sf::Color::Black);
	container->addObjectList("q6_nb", _nb_q6);

	_base._monitor->addObjectToDraw("data_games", container, -1);
}

void irc::shackTexture::initNbPlayer()
{
	auto container = new irc::Container(sf::IntRect(10, 260, WIDTH - 10, 100));
	container->setBoolUsed(false);

	auto title = new irc::Text("extra/Gobold.otf", sf::IntRect(0, 0, 100, 20), "Data Square:");
	title->setColor(sf::Color::Black);
	container->addObjectList("title", title);

	_nb_player = new irc::Text("extra/arial.ttf", sf::IntRect(0, 25, 100, 20), "??? player(s)");
	_nb_player->setColor(sf::Color::Black);
	container->addObjectList("nb_player", _nb_player);

	_base._monitor->addObjectToDraw("shack_server", container, -1);
}

void irc::shackTexture::initHeader()
{
	auto container = new irc::Container(sf::IntRect(0, 0, WIDTH, 235));
	container->setBoolUsed(false);
	std::string text = "0 : 0";

	auto user = new irc::Sprite("extra/gui/floor_icon.png", sf::IntRect(70, 20, 160, 160));
	_nickShack = new irc::Text("extra/arial.ttf", sf::IntRect(145 - (int)(text.size() / 2 * 13), 180, (int)(text.size() / 2 * 13), 26), text);
	auto sep = new irc::Sprite("extra/gui/separator.png", sf::IntRect(0, 220, WIDTH, 15));
	_nickShack->setColor(sf::Color(50, 50, 50));

	container->addObjectList("icon", user);
	container->addObjectList("text", _nickShack);
	container->addObjectList("sep", sep);
	_base._monitor->addObjectToDraw("shack_header", container, -1);
}

void irc::shackTexture::initBck()
{
	auto bck = new irc::Square(sf::IntRect(0, 0, WIDTH, HEIGHT));
	bck->setColor(sf::Color(240, 240, 240, 255));
	_base._monitor->addObjectToDraw("background", bck, -1);
}