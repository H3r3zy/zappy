/*
** EPITECH PROJECT, 2018
** client
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <Class/Gui/PersonalizedObject/TextInputBckPlaceHolder.hpp>
#include <Class/Communication.hpp>
#include "Gui.hpp"
#include "IATexture.hpp"

zap::IATexture::IATexture(zap::Gui &base) : _base(base)
{
}

void zap::IATexture::initTexture()
{
	initBck();
	initUser();
	initDataServer();
	initDataGame();

	initArrow();
	initClose();

	_base._monitor->addFuncLoop(1, [this] {
		if (_base._comm._listId.empty()) {
			_base._monitor->setScene(0);
			return;
		} else if (_base._comm._listId[0] == -1) {
			_base._monitor->setScene(-1);
			return;
		}

		_base._comm._player.id = _base._comm._listId[0];

		ulong idx = 0;
		for (auto &&iconTeam : _base._comm._teamName) {
			if (iconTeam == _base._comm._player.team) {
				for (auto &&it : _icon_team) {
					it->setBoolDisplay(false);
				}
				_icon_team[idx % 3]->setBoolDisplay(true);
				break;
			}
			++idx;
		}

		_base._monitor->getObjectByName("arrow_change", 1)->setBoolDisplay(_base._comm._listId.size() != 1);
		_nb_q0->setText("x "+ std::to_string(_base._comm._player.ressources.q0));
		_nb_q1->setText("x "+ std::to_string(_base._comm._player.ressources.q1));
		_nb_q2->setText("x "+ std::to_string(_base._comm._player.ressources.q2));
		_nb_q3->setText("x "+ std::to_string(_base._comm._player.ressources.q3));
		_nb_q4->setText("x "+ std::to_string(_base._comm._player.ressources.q4));
		_nb_q5->setText("x "+ std::to_string(_base._comm._player.ressources.q5));
		_nb_q6->setText("x "+ std::to_string(_base._comm._player.ressources.q6));
		_status->setText("Level: " + std::to_string(_base._comm._player.level));
		_pos->setText("Position: " + std::to_string((int)_base._comm._player._pos.first) + ", " + std::to_string((int)_base._comm._player._pos.second));

		_team->setText("Team name: " + _base._comm._player.team);
		std::string id = std::to_string(_base._comm._player.id);
		_nickIA->setPos(sf::IntRect(145 - (int)(id.size() / 2 * 13), 180, (int)(id.size() / 2 * 13), 26));
		_nickIA->setText(id);
	});
	_base._monitor->addFuncLoop(1, &zap::IATexture::updateIAData, this);
}

void zap::IATexture::updateIAData()
{
	static auto begin = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

	auto end = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

	int ms = end - begin;
	if (ms > 700) {
		begin = end;
		_base._comm.writeOnServer("pin " + std::to_string(_base._comm._listId[0]));
	}

	_base._comm.lockGui();
	auto list_msg = _base._comm.getEnqueueGui();

	for (auto &&it : list_msg) {
		if (it.getCommandName() == "pin") {
			std::cerr << "inventory: " << it.getCommand()[3] << ", " << it.getCommand()[4] << ", " << it.getCommand()[5] << ", " << it.getCommand()[6] << ", "<< it.getCommand()[7] << ", " << it.getCommand()[8] << ", " << it.getCommand()[9] << ", " <<  std::endl;
			_base._comm._player.ressources.q0 = it.getCommand()[3];
			_base._comm._player.ressources.q1 = it.getCommand()[4];
			_base._comm._player.ressources.q2 = it.getCommand()[5];
			_base._comm._player.ressources.q3 = it.getCommand()[6];
			_base._comm._player.ressources.q4 = it.getCommand()[7];
			_base._comm._player.ressources.q5 = it.getCommand()[8];
			_base._comm._player.ressources.q6 = it.getCommand()[9];
		} else if (it.getCommandName() == "eht" || it.getCommandName() == "edi")
			_base._comm._server.eggs--;
		else if (it.getCommandName() == "bfk")
			_base._comm._server.eggs++;
	}
	_base._comm.getEnqueueGui().clear();
	_base._comm.unlockGui();

}

void zap::IATexture::initClose()
{
	auto close = new zap::Sprite("extra/gui/close.png", sf::IntRect(250, 10, 30, 30));

	close->addFuncMouseEvent(zap::MouseEvent::CLICK, [this] {
		if (_base._comm._listId.size() == 1) {
			_base._comm._listId.clear();
			_base._monitor->setScene(0);
			return;
		}
		_base._comm._listId.erase(_base._comm._listId.begin());
		if (_base._comm._listId[0] == -1)
			_base._monitor->setScene(-1);
	});
	_base._monitor->addObjectToDraw("close", close, 1, 2);
}

void zap::IATexture::initArrow()
{
	auto container = new zap::Container(sf::IntRect(10, 0, WIDTH - 10, HEIGHT));

	auto arrow_left = new zap::Sprite("extra/gui/arrow.png", sf::IntRect(0, 100, 50, 40));
	container->addObjectList("arrow_left", arrow_left, 1);
	auto arrow_right = new zap::Sprite("extra/gui/arrow_right.png", sf::IntRect(230, 100, 50, 40));
	container->addObjectList("arrow_right", arrow_right, 1);

	auto arrow_left_hover = new zap::Sprite("extra/gui/arrow_hover.png", sf::IntRect(0, 100, 50, 40));
	container->addObjectList("arrow_left_hover", arrow_left_hover, 0);
	auto arrow_right_hover = new zap::Sprite("extra/gui/arrow_right_hover.png", sf::IntRect(230, 100, 50, 40));
	container->addObjectList("arrow_right_hover", arrow_right_hover, 0);

	arrow_left_hover->addFuncMouseEvent(zap::MouseEvent::HOVER, [arrow_left_hover] {arrow_left_hover->setLayer(12);});
	arrow_left_hover->addFuncMouseEvent(zap::MouseEvent::HOVEROUT, [arrow_left_hover] {arrow_left_hover->setLayer(0);});

	arrow_right_hover->addFuncMouseEvent(zap::MouseEvent::HOVER, [arrow_right_hover] {arrow_right_hover->setLayer(12);});
	arrow_right_hover->addFuncMouseEvent(zap::MouseEvent::HOVEROUT, [arrow_right_hover] {arrow_right_hover->setLayer(0);});

	arrow_left->addFuncMouseEvent(zap::MouseEvent::CLICK, [this] {
		int save = _base._comm._listId[0];
		_base._comm._listId.erase(_base._comm._listId.begin());
		_base._comm._listId.push_back(save);

		if (_base._comm._listId[0] == -1)
			_base._monitor->setScene(-1);
	});

	arrow_right->addFuncMouseEvent(zap::MouseEvent::CLICK, [this] {
		int save = _base._comm._listId[_base._comm._listId.size() - 1];
		_base._comm._listId.pop_back();
		_base._comm._listId.insert(_base._comm._listId.begin(), save);

		if (_base._comm._listId[0] == -1)
			_base._monitor->setScene(-1);
	});

	_base._monitor->addObjectToDraw("arrow_change", container, 1, 10);
}

void zap::IATexture::initDataGame()
{
	auto container = new zap::Container(sf::IntRect(10, 380, WIDTH - 10, HEIGHT - 380));
	container->setBoolUsed(false);

	auto title = new zap::Text("extra/Gobold.otf", sf::IntRect(0, 0, 100, 20), "Inventory:");
	title->setColor(sf::Color::Black);
	container->addObjectList("title", title);

	container->addObjectList("q0", new zap::Sprite("extra/gui/baie.png", sf::IntRect(0, 40, 40, 50)));
	_nb_q0 = new zap::Text("extra/arial.ttf", sf::IntRect(60, 55, 80, 20), "x ???");
	_nb_q0->setColor(sf::Color::Black);
	container->addObjectList("q0_nb", _nb_q0);

	container->addObjectList("q1", new zap::Sprite("extra/gui/list_pokeballs.png", sf::IntRect(0, 100, 50, 50), sf::IntRect(0, 0, 60, 60)));
	_nb_q1 = new zap::Text("extra/arial.ttf", sf::IntRect(60, 115, 80, 20), "x ???");
	_nb_q1->setColor(sf::Color::Black);
	container->addObjectList("q1_nb", _nb_q1);

	container->addObjectList("q2", new zap::Sprite("extra/gui/list_pokeballs.png", sf::IntRect(0, 160, 50, 50), sf::IntRect(60, 0, 60, 60)));
	_nb_q2 = new zap::Text("extra/arial.ttf", sf::IntRect(60, 175, 80, 20), "x ???");
	_nb_q2->setColor(sf::Color::Black);
	container->addObjectList("q2_nb", _nb_q2);

	container->addObjectList("q3", new zap::Sprite("extra/gui/list_pokeballs.png", sf::IntRect(0, 220, 50, 50), sf::IntRect(120, 0, 60, 60)));
	_nb_q3 = new zap::Text("extra/arial.ttf", sf::IntRect(60, 235, 80, 20), "x ???");
	_nb_q3->setColor(sf::Color::Black);
	container->addObjectList("q3_nb", _nb_q3);

	container->addObjectList("q4", new zap::Sprite("extra/gui/list_pokeballs.png", sf::IntRect(150, 40, 50, 50), sf::IntRect(180, 0, 60, 60)));
	_nb_q4 = new zap::Text("extra/arial.ttf", sf::IntRect(210, 55, 80, 20), "x ???");
	_nb_q4->setColor(sf::Color::Black);
	container->addObjectList("q4_nb", _nb_q4);

	container->addObjectList("q5", new zap::Sprite("extra/gui/list_pokeballs.png", sf::IntRect(150, 100, 50, 50), sf::IntRect(180, 120, 60, 60)));
	_nb_q5 = new zap::Text("extra/arial.ttf", sf::IntRect(210, 115, 80, 20), "x ???");
	_nb_q5->setColor(sf::Color::Black);
	container->addObjectList("q5_nb", _nb_q5);

	container->addObjectList("q6", new zap::Sprite("extra/gui/list_pokeballs.png", sf::IntRect(150, 160, 50, 50), sf::IntRect(240, 180, 60, 60)));
	_nb_q6 = new zap::Text("extra/arial.ttf", sf::IntRect(210, 175, 80, 20), "x ???");
	_nb_q6->setColor(sf::Color::Black);
	container->addObjectList("q6_nb", _nb_q6);

	_base._monitor->addObjectToDraw("data_games", container, 1);
}

void zap::IATexture::initDataServer()
{
	auto container = new zap::Container(sf::IntRect(10, 260, WIDTH - 10, 100));
	container->setBoolUsed(false);

	auto title = new zap::Text("extra/Gobold.otf", sf::IntRect(0, 0, 100, 20), "AI Data:");
	title->setColor(sf::Color::Black);
	container->addObjectList("title", title);

	_team = new zap::Text("extra/arial.ttf", sf::IntRect(0, 25, 100, 20), "Team name: ???");
	_team->setColor(sf::Color::Black);
	container->addObjectList("team_name", _team);

	_pos = new zap::Text("extra/arial.ttf", sf::IntRect(0, 50, 100, 20), "Position: ???, ???");
	_pos->setColor(sf::Color::Black);
	container->addObjectList("pos", _pos);

	_status = new zap::Text("extra/arial.ttf", sf::IntRect(0, 75, 100, 20), "Level: ???");
	_status->setColor(sf::Color::Black);
	container->addObjectList("status", _status);

	_base._monitor->addObjectToDraw("data_ia", container, 1);
}

void zap::IATexture::initUser()
{
	auto container = new zap::Container(sf::IntRect(0, 0, WIDTH, 235));
	container->setBoolUsed(false);
	std::string id = std::to_string(1);

	_icon_team.push_back(new zap::Sprite("extra/gui/team_1.png", sf::IntRect(70, 20, 160, 160)));
	_icon_team.push_back(new zap::Sprite("extra/gui/team_2.png", sf::IntRect(70, 20, 160, 160)));
	_icon_team.push_back(new zap::Sprite("extra/gui/team_3.png", sf::IntRect(70, 20, 160, 160)));

	_nickIA = new zap::Text("extra/arial.ttf", sf::IntRect(145 - (int)(id.size() / 2 * 13), 180, (int)(id.size() / 2 * 13), 26), id);
	auto sep = new zap::Sprite("extra/gui/separator.png", sf::IntRect(0, 220, WIDTH, 15));
	_nickIA->setColor(sf::Color(50, 50, 50));

	int idx = 1;
	for (auto &&item : _icon_team) {
		container->addObjectList("ia_picture" + idx, item);
		++idx;
	}

	container->addObjectList("ia_nick", _nickIA);
	container->addObjectList("ia_sep", sep);
	_base._monitor->addObjectToDraw("ia_header", container, 1);
}

void zap::IATexture::initBck()
{
	auto bck = new zap::Square(sf::IntRect(0, 0, WIDTH, HEIGHT));
	bck->setColor(sf::Color(240, 240, 240, 255));
	_base._monitor->addObjectToDraw("background", bck, 1);
}
