/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <regex>
#include <wait.h>
#include "ManageServer.hpp"
#include "ManageDisplay.hpp"
#include "Auth.hpp"
#include "IncludeGui.hpp"

zap::Auth::Auth(int width, int height) : _base("Authentication", (ulong)width, (ulong)height), _height(height), _width(width)
{
	initBck();
	initSubmit();
	initTextInput();
	initPlaceHolder();
	initSounds();
	_base.addFuncLoop(0, &zap::Auth::loopErrorDisplay, this);

	if (!_music.openFromFile("extra/gui/menu.ogg"))
		throw std::exception();
	_music.setLoop(true);
	_music.play();
	_base.loopWindow(nullptr);
}

zap::Auth::~Auth()
{
	_music.stop();
}

void zap::Auth::initSounds()
{
	zap::Sprite *sounds = new zap::Sprite("extra/gui/sounds.png", sf::IntRect(1100, 50, 50, 50));
	zap::Sprite *sounds_off = new zap::Sprite("extra/gui/sounds_off.png", sf::IntRect(1100, 50, 50, 50));
	zap::Square *hit_box = new zap::Square(sf::IntRect(1100, 50, 50, 50));
	sounds_off->setBoolDisplay(false);

	_base.addObjectToDraw("sounds_off", sounds_off, 0, 5);
	_base.addObjectToDraw("sounds", sounds, 0, 5);
	_base.addObjectToDraw("hit_box", hit_box, 0, 0);

	hit_box->addFuncMouseEvent(zap::MouseEvent::CLICK, [this, sounds, sounds_off] {
		if (!sounds->getBoolDisplay()) {
			_music.play();
			sounds->setBoolDisplay(true);
			sounds_off->setBoolDisplay(false);
		} else {
			_music.pause();
			sounds->setBoolDisplay(false);
			sounds_off->setBoolDisplay(true);
		}
	});
}

void zap::Auth::initBck()
{
	zap::Sprite *background = new zap::Sprite("extra/gui/background_menu.png", sf::IntRect(0, 0, _width, _height));
	background->addFuncKeyEvent(sf::Keyboard::Escape, &zap::SFML_monitor::closeWindow, std::ref(_base));

	zap::Square *bck_input_nick_border = new zap::Square(sf::IntRect(400, 250, 400, 60));
	zap::Square *bck_input_ip_border = new zap::Square(sf::IntRect(400, 380, 250, 60));
	zap::Square *bck_input_port_border = new zap::Square(sf::IntRect(700, 380, 100, 60));

	_base.addObjectToDraw("background", background);
	_base.addObjectToDraw("title_auth", new zap::Text("extra/Gobold.otf", sf::IntRect(330, 100, 280, 70), "Zappy Zappy Rouge"));

	_base.addObjectToDraw("title_input_nick", new zap::Text("extra/arial.ttf", sf::IntRect(400, 220, 400, 20), "Nickname:"));
	_base.addObjectToDraw("bck_input_nick_border", bck_input_nick_border);

	_base.addObjectToDraw("title_input_ip", new zap::Text("extra/arial.ttf", sf::IntRect(400, 350, 400, 20), "Server address:"));
	_base.addObjectToDraw("bck_input_ip_border", bck_input_ip_border);

	_base.addObjectToDraw("title_input_port", new zap::Text("extra/arial.ttf", sf::IntRect(700, 350, 400, 20), "Port:"));
	_base.addObjectToDraw("bck_input_port_border", bck_input_port_border);

}

void zap::Auth::initSubmit()
{
	zap::Square *button_submit = new zap::Square(sf::IntRect(500, 490, 200, 60));
	button_submit->setColor(sf::Color(130, 204, 221));
	button_submit->addFuncMouseEvent(CLICK, &zap::Auth::sendForm, this);

	zap::Text *text_submit = new zap::Text("extra/Gobold.otf", sf::IntRect(555, 502, 170, 30), "submit");
	text_submit->setLayer(2);

	zap::Square *submit_hover = new zap::Square(sf::IntRect(500, 490, 200, 60));
	submit_hover->setColor(sf::Color(0, 0, 0, 50));
	submit_hover->setLayer(0);
	dynamic_cast<AbstractObjectSFML *>(submit_hover)->addFuncMouseEvent(HOVEROUT, &zap::Auth::setLayer, this, submit_hover, 0);
	dynamic_cast<AbstractObjectSFML *>(submit_hover)->addFuncMouseEvent(HOVER, &zap::Auth::setLayer, this, submit_hover, 1);

	_base.addObjectToDraw("submit_text", text_submit);
	_base.addObjectToDraw("submit", button_submit);
	_base.addObjectToDraw("submit_hover", submit_hover);
}

void zap::Auth::initPlaceHolder()
{
	zap::Text *nick_placeholder = new zap::Text("extra/arial.ttf", sf::IntRect(410, 260, 380, 30), "Your nickname");
	nick_placeholder->setColor(sf::Color(150, 150, 150));

	zap::Text *ip_placeholder = new zap::Text("extra/arial.ttf", sf::IntRect(410, 390, 230, 30), "IP address");
	ip_placeholder->setColor(sf::Color(150, 150, 150));

	zap::Text *port_placeholder = new zap::Text("extra/arial.ttf", sf::IntRect(710, 390, 90, 30), "Port");
	port_placeholder->setColor(sf::Color(150, 150, 150));
	port_placeholder->setLayer(0);

	_base.addObjectToDraw("nick_placeholder", nick_placeholder);
	_base.addObjectToDraw("ip_placeholder", ip_placeholder);
	_base.addObjectToDraw("port_placeholder", port_placeholder);

	inputTextWrite(port_placeholder, _base.getObjectByName("input_port"), 0);
	inputTextWrite(port_placeholder, _base.getObjectByName("input_port"), 1);

	_base.getObjectByName("bck_input_nick_border")->addFuncMouseEvent(CLICK, &zap::Auth::inputTextWrite, this, nick_placeholder, _base.getObjectByName("input_nick"), 0);
	_base.getObjectByName("bck_input_nick_border")->addFuncMouseEvent(CLICKOUT, &zap::Auth::inputTextWrite, this, nick_placeholder, _base.getObjectByName("input_nick"), 1);

	_base.getObjectByName("bck_input_ip_border")->addFuncMouseEvent(CLICK, &zap::Auth::inputTextWrite, this, ip_placeholder, _base.getObjectByName("input_ip"), 0);
	_base.getObjectByName("bck_input_ip_border")->addFuncMouseEvent(CLICKOUT, &zap::Auth::inputTextWrite, this, ip_placeholder, _base.getObjectByName("input_ip"), 1);

	_base.getObjectByName("bck_input_port_border")->addFuncMouseEvent(CLICK, &zap::Auth::inputTextWrite, this, port_placeholder, _base.getObjectByName("input_port"), false);
	_base.getObjectByName("bck_input_port_border")->addFuncMouseEvent(CLICKOUT, &zap::Auth::inputTextWrite, this, port_placeholder, _base.getObjectByName("input_port"), true);
}

void zap::Auth::initTextInput()
{
	zap::TextInput *nick_input = new zap::TextInput("extra/arial.ttf", sf::IntRect(410, 260, 380, 30));
	nick_input->setColor(sf::Color::Black);
	nick_input->setLayer(0);
	nick_input->setBoolUsed(false);

	zap::TextInput *ip_input = new zap::TextInput("extra/arial.ttf", sf::IntRect(410, 390, 230, 30));
	ip_input->setColor(sf::Color::Black);
	ip_input->setLayer(0);
	ip_input->setBoolUsed(false);

	zap::TextInput *port_input = new zap::TextInput("extra/arial.ttf", sf::IntRect(710, 390, 90, 30));
	port_input->setColor(sf::Color::Black);
	port_input->setPrompt("8888");
	port_input->setBoolUsed(false);

	nick_input->addFuncKeyEvent(sf::Keyboard::Tab, &zap::Auth::GoToTheNextInput, this, nick_input, ip_input, 0);
	ip_input->addFuncKeyEvent(sf::Keyboard::Tab, &zap::Auth::GoToTheNextInput, this, ip_input, port_input, 1);
	port_input->addFuncKeyEvent(sf::Keyboard::Tab, &zap::Auth::GoToTheNextInput, this, port_input, nick_input, 2);

	nick_input->addFuncKeyEvent(sf::Keyboard::Return, &zap::Auth::sendForm, this);
	ip_input->addFuncKeyEvent(sf::Keyboard::Return, &zap::Auth::sendForm, this);
	port_input->addFuncKeyEvent(sf::Keyboard::Return, &zap::Auth::sendForm, this);

	_base.addObjectToDraw("input_port", port_input);
	_base.addObjectToDraw("input_ip", ip_input);
	_base.addObjectToDraw("input_nick", nick_input);
}

void zap::Auth::inputTextWrite(zap::IObjectSFML *placeholder, zap::IObjectSFML *input_obj, bool layer)
{
	auto input = dynamic_cast<TextInput *>(input_obj);

	if (!layer) {
		input->setLayer(1);
		input->setBlockPrompt(false);
		input->setBoolUsed(true);
		placeholder->setLayer((std::size_t)layer);
	} else {
		if (input->getPrompt().empty())
			placeholder->setLayer((std::size_t)layer);
		else
			input->setLayer(1);
		input->setBoolUsed(false);
		input->setBlockPrompt(true);
	}
}

void zap::Auth::setLayer(zap::IObjectSFML *placeholder, const std::size_t &layer)
{
	placeholder->setLayer(layer);
}

void zap::Auth::sendForm()
{
	bool error = false;
	_nick = dynamic_cast<TextInput *>(_base.getObjectByName("input_nick"))->getPrompt();
	_ip = dynamic_cast<TextInput *>(_base.getObjectByName("input_ip"))->getPrompt();
	_port = dynamic_cast<TextInput *>(_base.getObjectByName("input_port"))->getPrompt();
	if (_ip.empty()) {
		error = true;
		_base.getObjectByName("bck_input_ip_border")->setColor(sf::Color(222, 170, 170));
	} else
		_base.getObjectByName("bck_input_ip_border")->setColor(sf::Color::White);
	if (!std::regex_match(_port, std::regex("\\d+"))) {
		error = true;
		_base.getObjectByName("bck_input_port_border")->setColor(sf::Color(222, 170, 170));
	} else
		_base.getObjectByName("bck_input_port_border")->setColor(sf::Color::White);
	if (_nick.empty() || _nick.find(" ") != std::string::npos || _nick.size() > 20) {
		error = true;
		_base.getObjectByName("bck_input_nick_border")->setColor(sf::Color(222, 170, 170));
	} else
		_base.getObjectByName("bck_input_nick_border")->setColor(sf::Color::White);
	tryToConnect(error);
}

bool zap::Auth::checkConnection()
{
	_socketServer = zap::ManageServer::getFileDescriptorSocket();
	if (_socketServer < 0) {
		modalError("Can't create the socket");
		return true;
	}
	if (!zap::ManageServer::connectServer(_socketServer, _ip, _port).empty()) {
		modalError("Can't connect to the server");
		return true;
	}
	if (zap::ManageServer::readServer(_socketServer, true) != "WELCOME\n") {
		modalError("Not a zappy server");
		return true;
	}
	if (zap::ManageServer::writeOnServer(_socketServer, "gui\n") == -1) {
		modalError("Can't write on server");
		return true;
	}
	if (zap::ManageServer::readServer(_socketServer, true) != "ok\n") {
		modalError("Can't login");
	}
	return false;
}

void zap::Auth::tryToConnect(bool error)
{
	if (error)
		modalError("One or more inputs are wrong or missing");
	else if (!checkConnection()) {
		_base.closeWindow();
		ManageDisplay(_socketServer, _nick, _ip, _music);
	}
}

void zap::Auth::GoToTheNextInput(zap::IObjectSFML *from, zap::IObjectSFML *to, int step)
{
	static auto begin = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	static bool check = false;
	IObjectSFML *placeFrom;
	IObjectSFML *placeTo;

	auto end = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	long ms = end - begin;
	if (ms < 100 && check)
		return;
	check = true;
	begin = end;
	if (step == 0) {
		placeFrom = _base.getObjectByName("nick_placeholder");
		placeTo = _base.getObjectByName("ip_placeholder");
	} else if (step == 1) {
		placeFrom = _base.getObjectByName("ip_placeholder");
		placeTo = _base.getObjectByName("port_placeholder");
	} else {
		placeFrom = _base.getObjectByName("port_placeholder");
		placeTo = _base.getObjectByName("nick_placeholder");
	}
	inputTextWrite(placeFrom, from, 1);
	inputTextWrite(placeTo, to, 0);
}


void zap::Auth::loopErrorDisplay()
{
	static auto begin = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	static zap::Container *error = nullptr;

	auto end = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	long int ms = end - begin;
	if (error == nullptr && _listError.empty())
		return;
	else if (error == nullptr && !_listError.empty()) {
		error = new zap::Container(sf::IntRect(0, 800, 1200, 30));
		zap::Modal *error_modal = new zap::Modal(error, sf::Vector2i(0, 750), 16);
		zap::Square *bck_error = new zap::Square(sf::IntRect(0, 0, 1200, 50));
		zap::Text *text_error = new zap::Text("extra/arial.ttf", sf::IntRect(10, 5, 1130, 30), _listError[0]);
		bck_error->setColor(sf::Color(229, 80, 57, 200));
		error->addObjectList("bck_error", bck_error, _base.getCurrentScene());
		error->addObjectList("text_error", text_error, _base.getCurrentScene());
		_base.addObjectToDraw("error_modal", error_modal, _base.getCurrentScene(), 900);
		_listError.erase(_listError.begin());
		begin = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	} else if (ms > 5000){
		_base.deleteObjectByName("error_modal", _base.getCurrentScene());
		error = nullptr;
	}
}

void zap::Auth::modalError(std::string error)
{
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	std::time_t now_c = std::chrono::system_clock::to_time_t(now - std::chrono::hours(24));
	std::stringstream ss;
	ss << std::put_time(std::localtime(&now_c), "%H:%M:%S - ");
	if (error.size() > 180) {
		error = error.substr(0, 177);
		error += "...";
	}
	std::string msg = ss.str() + error;
	_listError.push_back(msg);
}