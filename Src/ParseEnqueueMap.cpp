//
// Created by wisenoa on 20/06/18.
//


#include <SFML/System.hpp>
#include <Class/Communication.hpp>
#include "ParseEnqueueMap.hpp"
#include "Map.hpp"

zap::ParseEnqueueMap::ParseEnqueueMap(zap::Communication &comm) : _comm(comm)
{
	_comm.writeOnServer("msz");
}

sf::Vector2f zap::ParseEnqueueMap::ParseMapSize()
{
	sf::Vector2f tmpMap = {0, 0};


	std::vector<CstringArray> save;

	usleep(10000);
	while (true) {
		int i = 0;
		_comm.lockMap();
		std::vector<CstringArray> &test = _comm.getEnqueueMap();
		_comm.unlockMap();
		save.clear();
		for (const auto &it : test) {
			auto tmpPrint = it.getCommand();
			if (it.getCommandName() == "msz") {
				tmpMap.x = tmpPrint[0];
				tmpMap.y = tmpPrint[1];
				_comm.lockMap();
				_comm.setEnqueueMap(save);
				_comm.unlockMap();
				return tmpMap;
			} else {
				save.push_back(it);
			}
			i++;
		}
	}
}

void zap::ParseEnqueueMap::fillMap(Map &map, sf::Vector2f &mapSize)
{
	_comm.writeOnServer("bct 0 0");
	_comm.writeOnServer("mct");
	std::vector<CstringArray> save;
	bool end = false;
	bool stillCell = false;
	while (!end) {
		_comm.lockMap();
		std::vector<CstringArray> &test = _comm.getEnqueueMap();
		_comm.unlockMap();
		_blocNumber = 0;
		if (test.size() < ((mapSize.x - 1) * (mapSize.y - 1) + save.size())) {
			usleep(400000);
			continue;
		}
		save.clear();
		_comm.lockMap();
		for (const auto &it : test) {

			if (it.getCommandName() == "bct") {
				auto tmpPrint = it.getCommand();
				if (tmpPrint[0] < mapSize.x && tmpPrint[1] < mapSize.y) {

				/* Q1 => Q6 */
				map.getGrid().getCell(tmpPrint[0], tmpPrint[1])->setRessources(0, tmpPrint[2]);
				map.getGrid().getCell(tmpPrint[0], tmpPrint[1])->setRessources(1, tmpPrint[3]);
				map.getGrid().getCell(tmpPrint[0], tmpPrint[1])->setRessources(2, tmpPrint[4]);
				map.getGrid().getCell(tmpPrint[0], tmpPrint[1])->setRessources(3, tmpPrint[5]);
				map.getGrid().getCell(tmpPrint[0], tmpPrint[1])->setRessources(4, tmpPrint[6]);
				map.getGrid().getCell(tmpPrint[0], tmpPrint[1])->setRessources(5, tmpPrint[7]);
				map.getGrid().getCell(tmpPrint[0], tmpPrint[1])->setRessources(6, tmpPrint[8]);

				_comm._server.ressources.q6 += tmpPrint[2];

				_comm._server.ressources.q1 += tmpPrint[3];
				_comm._server.ressources.q2 += tmpPrint[4];
				_comm._server.ressources.q3 += tmpPrint[5];

				_comm._server.ressources.q4 += tmpPrint[6];
				_comm._server.ressources.q5 += tmpPrint[7];
				_comm._server.ressources.q0 += tmpPrint[8];


				/* Food */
				_blocNumber++;
				//
				if (tmpPrint[0] == mapSize.x - 1 && tmpPrint[1] == mapSize.y - 1) {
					_ready = true;
					_comm.setEnqueueMap(save);
					_comm.unlockMap();
					end = true;
					break;
				}
				}
			} else {
				save.push_back(it);
			}
		}
		stillCell = false;
		for (const auto &it : save) {
			if (it.getCommandName() == "bct")
				stillCell = true;
		}
		if (!stillCell) {
			_blocNumber = 0;
			_comm.writeOnServer("mct");
		}
		_comm.setEnqueueMap(save);
		_comm.unlockMap();
		usleep(400000);
	}
	end = false;
	_comm.writeOnServer("sgt");
	usleep(10000);
	while (!end) {
		_comm.lockMap();
		for (const auto &it : _comm.getEnqueueMap()) {
			//	window.clear(sf::Color::Black);
			if (it.getCommandName() == "sgt") {
				_comm.setFreq(it.getCommand()[0]);

				end = true;
				break;
			}
		}
		_comm.unlockMap();
		usleep(10000);
	}

}


void zap::ParseEnqueueMap::loadingDisplay( sf::Vector2f &mapSize, sf::RenderWindow &window)
{
	window.setActive(true);
	sf::Text text;
	sf::Font font;
	std::string total = std::to_string(mapSize.x * mapSize.y);
	total.erase (total.find_last_not_of('0'), std::string::npos);
	float totalNb = (mapSize.x * mapSize.y);
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Texture texture_bck;
	sf::Sprite bck;

	sf::RectangleShape totalRect;
	totalRect.setFillColor(sf::Color(0, 80, 0, 122));
	totalRect.setSize(sf::Vector2f(500, 50));
	totalRect.setPosition(290, 490);

	sf::RectangleShape currentRect;
	currentRect.setFillColor(sf::Color::Green);
	currentRect.setSize(sf::Vector2f(0, 50));
	currentRect.setPosition(290, 490);

	if (!texture.loadFromFile("extra/game/ronflex.png"))
		throw std::exception();
	sprite.setTexture(texture);

	if (!texture_bck.loadFromFile("extra/game/loading_bck.png"))
		throw std::exception();
	bck.setTexture(texture_bck);
	bck.setScale(sf::Vector2f(1.5, 1.5));

	if (!font.loadFromFile("extra/pokemon.ttf"))
		throw std::exception();
	text.setFont(font);
	text.setCharacterSize(20);

	while (!_ready) {
		if (_blocNumber != 0) {
			text.setString("Filling resources : " + std::to_string(_blocNumber) + " / " + total);
		} else {
			text.setString("Waiting Data response from server (Current data send :" + std::to_string(_comm.getEnqueueMap().size()) + ")");

		}
		currentRect.setSize(sf::Vector2f((_blocNumber / totalNb) * 500, 50));
		window.draw(bck);
		window.draw(sprite);
		window.draw(totalRect);
		window.draw(currentRect);
		window.draw(text);
		window.display();
		window.clear(sf::Color::Black);
	}
}

void zap::ParseEnqueueMap::parseNextCommand(zap::Map &map)
{
	int i = 0;
	_comm.lockMap();
	for (const auto &it : _comm.getEnqueueMap()) {
		if (it.getCommand().empty()) {

			_comm.getEnqueueMap().erase(_comm.getEnqueueMap().begin());
			break;
		}
		if (it.getCommandName() == "pnw") {
			addPlayer(map, it);
		} else if (it.getCommandName() == "pdi") {
			deletePlayer(map, it);
		}  else if (it.getCommandName() == "pmv") {
			movePlayerPosition(map, it);
		} else if (it.getCommandName() == "ptu") {
			movePlayerOrientation(map, it);
		} else if (it.getCommandName() == "pgt") {
			takeResourcePlayer(map, it);
		} else if (it.getCommandName() == "pdr") {
			dropResourcePlayer(map, it);
		} else if (it.getCommandName() == "sgr") {
			addRandomResource(map, it);
		} else if (it.getCommandName() == "pic") {
			incantPlayer(map, it);
		} else if (it.getCommandName() == "pbc") {
			broadcastPlayer(map, it);
		} else if (it.getCommandName() == "pie") {
			endIncantation(map, it);
		} else if (it.getCommandName() == "pfk") {
			eggDropped(map, it);
		} else if (it.getCommandName() == "ebo") {
			eggHatching(map, it);
		} else if (it.getCommandName() == "eht") {

			eggHatching2(map, it);
		}
		_comm.getEnqueueMap().erase(_comm.getEnqueueMap().begin());

		i++;
		break;
	}
	_comm.unlockMap();
}

void zap::ParseEnqueueMap::addPlayer(zap::Map &map, const CstringArray &command)
{
	std::vector<uint> tmpCommand = command.getCommand();
	int tmpFreq = map.getComm().getFreq();

	sf::Vector2f tmp = {static_cast<float>(tmpCommand[1]) * 100.f, (static_cast<float>(tmpCommand[2]) * 100.f)};


	if (command.getTeamName().empty() || map.getGrid().getTextureCharacter().empty() || tmpCommand[0] == 0) {


	} else {
	map.getCharacterMap().emplace(tmpCommand[0], Character(map.getGrid().getTextureCharacter()[command.getTeamName()], tmp, tmpCommand[0], tmpFreq, map.getMapSize(), command.getTeamName()));
	for (auto &it : map.getCharacterMap()) {
		if (it.second.getPlayerID() == tmpCommand[0]) {
			it.second.setPlayerOrientation(static_cast<char>(tmpCommand[3]), 7);
			it.second.setPlayerTeam(command.getTeamName());
			it.second.setPlayerLevel(tmpCommand[4]);
			break;
		}
	}
	}
}

void zap::ParseEnqueueMap::deletePlayer(zap::Map &map, const CstringArray &command)
{

	std::map<uint, Character> &tmp = map.getCharacterMap();

	for (auto vec_it = (tmp).begin(); vec_it != (tmp).end(); ) {
		if (vec_it->second.getPlayerID() == command.getCommand()[0]) {
			tmp.erase(vec_it);
			break;
		} else {
			++vec_it;
		}
	}
	int idx = 0;
	for (auto &&it  : _comm._listId ) {
		if (static_cast<ulong>(it) == command.getCommand()[0]) {
			_comm._listId.erase(_comm._listId.begin() + idx);
			break;
		}
		idx++;
	}
}

bool zap::ParseEnqueueMap::movePlayerPosition(zap::Map &map, const CstringArray &command)
{
	sf::Vector2f tmpPos = {static_cast<float>(command.getCommand()[1]) * 100.f, static_cast<float>(command.getCommand()[2]) * 100.f};

	int tmpFreq = map.getComm().getFreq();

	if (map.getCharacterMap().find((command.getCommand()[0])) == map.getCharacterMap().end()) {
		return false;
	}
	map.getCharacterMap().at(command.getCommand()[0]).setPlayerMovement(tmpPos, command.getCommand()[3], tmpFreq, 7);
	return true;
}

void zap::ParseEnqueueMap::movePlayerOrientation(zap::Map &map, const CstringArray &command)
{
	if (command.getCommand()[0] == 768 || command.getCommand()[0] == 256|| command.getCommand()[0] == 0 || command.getCommand()[0] == 512)
		return;
	if (map.getCharacterMap().find((command.getCommand()[0])) == map.getCharacterMap().end()) {
		return;
	}
	map.getCharacterMap().at(command.getCommand()[0]).setPlayerOrientation(static_cast<char>(command.getCommand()[1]), 7);
}

bool zap::ParseEnqueueMap::takeResourcePlayer(zap::Map &map, const CstringArray &command)
{
	if (map.getCharacterMap().find((command.getCommand()[0])) == map.getCharacterMap().end()) {
		return false;
	}
	int tmpFreq = map.getComm().getFreq();
	map.getCharacterMap().at(command.getCommand()[0]).setPlayerTake(tmpFreq, 7);
	auto tmpX = static_cast<int>(map.getCharacterMap().at(command.getCommand()[0]).getPlayerPosition().x / 100);
	if (tmpX > map.getMapSize().x - 1)
		tmpX--;
	else if (tmpX < 0)
		tmpX = 0;

	auto tmpY = static_cast<int>(map.getCharacterMap().at(command.getCommand()[0]).getPlayerPosition().y / 100);
	if (tmpY > map.getMapSize().y - 1)
		tmpY--;
	else if (tmpY < 0)
		tmpY = 0;

	map.getGrid().getCell(tmpX, tmpY)->delResources(command.getCommand()[1]);

	if (command.getCommand()[1] == 6) {
		_comm._server.ressources.q0--;
	}
	else if (command.getCommand()[1] == 1) {
		_comm._server.ressources.q1--;
	}
	else if (command.getCommand()[1] == 2) {
		_comm._server.ressources.q2--;
	}
	else if (command.getCommand()[1] == 3) {
		_comm._server.ressources.q3--;
	}
	else if (command.getCommand()[1] == 4) {
		_comm._server.ressources.q4--;
	}
	else if (command.getCommand()[1] == 5) {
		_comm._server.ressources.q5--;
	}
	else if (command.getCommand()[1] == 0) {
		_comm._server.ressources.q6--;
	}
	return true;
}

bool zap::ParseEnqueueMap::dropResourcePlayer(zap::Map &map, const CstringArray &command)
{
	if (map.getCharacterMap().find((command.getCommand()[0])) == map.getCharacterMap().end()) {

		return false;
	}
	int tmpFreq = map.getComm().getFreq();
	map.getCharacterMap().at(command.getCommand()[0]).setPlayerTake(tmpFreq, 7);
	auto tmpX = static_cast<int>(map.getCharacterMap().at(command.getCommand()[0]).getPlayerPosition().x / 100);
	if (tmpX > map.getMapSize().x - 1)
		tmpX = static_cast<int>(map.getMapSize().x - 1);
	else if (tmpX < 0)
		tmpX = 0;
	auto tmpY = static_cast<int>(map.getCharacterMap().at(command.getCommand()[0]).getPlayerPosition().y / 100);
	if (tmpY > map.getMapSize().y - 1)
		tmpY = static_cast<int>(map.getMapSize().y - 1);
	else if (tmpY < 0)
		tmpY = 0;


	map.getGrid().getCell(tmpX, tmpY)->addRessources(command.getCommand()[1]);

	if (command.getCommand()[1] == 6) {
		_comm._server.ressources.q0++;

	}
	else if (command.getCommand()[1] == 1) {
		_comm._server.ressources.q1++;

	}
	else if (command.getCommand()[1] == 2) {
		_comm._server.ressources.q2++;

	}
	else if (command.getCommand()[1] == 3) {
		_comm._server.ressources.q3++;

	}
	else if (command.getCommand()[1] == 4) {
		_comm._server.ressources.q4++;

	}
	else if (command.getCommand()[1] == 5) {
		_comm._server.ressources.q5++;

	}
	else if (command.getCommand()[1] == 0) {
		_comm._server.ressources.q6++;

	}
	return true;
}

bool zap::ParseEnqueueMap::addRandomResource(zap::Map &map, const CstringArray &command)
{
	map.getGrid().getCell(command.getCommand()[0], command.getCommand()[1])->addRessources(command.getCommand()[2]);

	if (command.getCommand()[1] == 6) {
		_comm._server.ressources.q0++;

	}
	else if (command.getCommand()[1] == 1) {
		_comm._server.ressources.q1++;

	}
	else if (command.getCommand()[1] == 2) {
		_comm._server.ressources.q2++;

	}
	else if (command.getCommand()[1] == 3) {
		_comm._server.ressources.q3++;

	}
	else if (command.getCommand()[1] == 4) {
		_comm._server.ressources.q4++;

	}
	else if (command.getCommand()[1] == 5) {
		_comm._server.ressources.q5++;

	}
	else if (command.getCommand()[1] == 0) {
		_comm._server.ressources.q6++;

	}

	return true;
}

std::vector<std::string> &zap::ParseEnqueueMap::getTeam()
{
	std::vector<CstringArray> save;
	_comm.writeOnServer("tna");

	usleep(10000);

	int i = 1;
	while (i != 0) {
		_comm.lockMap();
		save.clear();
		i = 0;
		for (const auto &it : _comm.getEnqueueMap()) {

			//	window.clear(sf::Color::Black);
			if (it.getCommandName() == "tna") {

				tmpTeam.push_back(it.getTeamName());
				i++;
			} else {
				save.push_back(it);
			}

		}
		_comm.setEnqueueMap(save);
		_comm.unlockMap();
		usleep(10000);
	}
	return tmpTeam;
}

void zap::ParseEnqueueMap::incantPlayer(zap::Map &map, const CstringArray &command)
{
	sf::Vector2f tmpPos = {static_cast<float>(command.getCommand()[0]), static_cast<float>(command.getCommand()[1])};
	int i = 2;
	int tmpFreq = map.getComm().getFreq();
	while (command.getCommand()[i] != 0 && i < 10) {

		if (map.getCharacterMap().find((command.getCommand()[i])) == map.getCharacterMap().end()) {

			++i;
			continue;
		}

		map.getCharacterMap().at(command.getCommand()[i]).setPlayerIncant(tmpFreq, 300, tmpPos);
		++i;
	}
}

void zap::ParseEnqueueMap::broadcastPlayer(zap::Map &map, const CstringArray &command)
{
	int tmpFreq = map.getComm().getFreq();

	if (map.getCharacterMap().find((command.getCommand()[0])) != map.getCharacterMap().end()) {

		map.getCharacterMap().at(command.getCommand()[0]).setPlayerBroadcast(tmpFreq, 7);
	} else {

	}
}

void zap::ParseEnqueueMap::endIncantation(zap::Map &map, const CstringArray &command)
{
	int i = 0;
	bool oneTime = false;
	while (command.getCommand()[i] != 0 && i < 9) {

		if (map.getCharacterMap().find((command.getCommand()[i])) == map.getCharacterMap().end()) {

			++i;
			continue;
		}
		map.getCharacterMap().at(command.getCommand()[i]).levelUp();


		if (!oneTime) {
			auto tmpX = static_cast<int>(map.getCharacterMap().at(
				command.getCommand()[i]).getPlayerPosition().x / 100);
			if (tmpX > map.getMapSize().x - 1)
				tmpX = static_cast<int>(map.getMapSize().x - 1);
			else if (tmpX < 0)
				tmpX = 0;
			auto tmpY = static_cast<int>(map.getCharacterMap().at(
				command.getCommand()[i]).getPlayerPosition().y / 100);
			if (tmpY > map.getMapSize().y - 1)
				tmpY = static_cast<int>(map.getMapSize().y - 1);
			else if (tmpY < 0)
				tmpY = 0;
			map.getGrid().getCell(tmpX, tmpY)->dellAllResources();

			oneTime = true;
		}
		++i;
	}
}

void zap::ParseEnqueueMap::eggDropped(zap::Map &map, const CstringArray &command)
{
	if (map.getCharacterMap().find((command.getCommand()[0])) != map.getCharacterMap().end()) {
		sf::Vector2i tmp;
		tmp.x = static_cast<int>(map.getCharacterMap().at(command.getCommand()[0]).getPlayerPosition().x / 100);
		tmp.y = static_cast<int>(map.getCharacterMap().at(command.getCommand()[0]).getPlayerPosition().y / 100);
		map.getEggMap()[command.getCommand()[1]].second = tmp;
		map.getEggMap()[command.getCommand()[1]].first = map.getCharacterMap().at(command.getCommand()[0]).getPlayerTeam();


	} else {

	}
}

void zap::ParseEnqueueMap::eggHatching(zap::Map &map, const CstringArray &command)
{
	if (map.getEggMap().find(command.getCommand()[0]) != map.getEggMap().end()) {
		std::vector<uint> tmp;
		for (int i = 0; i < 9; i++) {
			tmp.emplace_back(0);
		}
		tmp[0] = command.getCommand()[1];
		tmp[1] = static_cast<unsigned int>(map.getEggMap()[command.getCommand()[0]].second.x);
		tmp[2] = static_cast<unsigned int>(map.getEggMap()[command.getCommand()[0]].second.y);

		tmp[3] = 8;
		tmp[4] = 1;
		CstringArray tmp2;
		tmp2.setCommand(tmp);
		tmp2.setTeamName(map.getEggMap()[command.getCommand()[0]].first);




		addPlayer(map, tmp2);
	}
}

void zap::ParseEnqueueMap::eggHatching2(zap::Map &map, const CstringArray &command)
{

	if (map.getCharacterMap().find((command.getCommand()[1])) != map.getCharacterMap().end()) {

		map.getCharacterMap().at(command.getCommand()[1]).setPlayerOrientation(1, 7);
		map.getEggMap().erase(command.getTeamName()[0]);
	}
}