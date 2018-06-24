//
// Created by wisenoa on 20/06/18.
//


#include <SFML/System.hpp>
#include <Class/Communication.hpp>
#include "ParseEnqueueMap.hpp"
#include "Map.hpp"

irc::ParseEnqueueMap::ParseEnqueueMap(irc::Communication &comm) : _comm(comm)
{
	_comm.writeOnServer("msz");
}

sf::Vector2f irc::ParseEnqueueMap::ParseMapSize()
{
	sf::Vector2f tmpMap = {0, 0};


	std::vector<CstringArray> save;

	bool loop = true;
	usleep(10000);
	while (true) {
		int i = 0;
		_comm.lockMap();
		std::vector<CstringArray> &test = _comm.getEnqueueMap();
		_comm.unlockMap();
		save.clear();
		//std::cerr << "size: " << test.size() << std::endl;
		for (const auto &it : test) {
			//std::cout << "Coammnde Name [" << it.getCommandName() << "]" << std::endl;
			auto tmpPrint = it.getCommand();
			if (tmpPrint.size() == 8) {
/*				std::cout << "Et son message est :"
					<< tmpPrint[0] << " " << tmpPrint[1]
					<< " " << tmpPrint[2] << " "
					<< tmpPrint[3] << " " << tmpPrint[4]
					<< " " << tmpPrint[5] << " "
					<< tmpPrint[6] << " " << tmpPrint[7]
					<< std::endl;*/
			}
			if (it.getCommandName() == "msz") {
				tmpMap.x = tmpPrint[0];
				tmpMap.y = tmpPrint[1];
				//std::cout << "je vais return un vector X" << tmpMap.x << " Y " << tmpMap.y << std::endl;
				_comm.lockMap();
				_comm.setEnqueueMap(save);
				_comm.unlockMap();
				return tmpMap;
			} else {
				save.push_back(it);
			}
			//std::cout << "je boucle dedans pour la " << i << " fois" << std::endl;
			i++;
		}
	}
}

void irc::ParseEnqueueMap::fillMap(Map &map, sf::Vector2f &mapSize)
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

			//	window.clear(sf::Color::Black);
			if (it.getCommandName() == "bct") {
				//std::cout << "Coammnde Name [" << it.getCommandName() << "]" << std::endl;
				auto tmpPrint = it.getCommand();
				if (tmpPrint[0] < mapSize.x && tmpPrint[1] < mapSize.y) {
//				if (tmpPrint.size() == 9)
					//std::cout << "Et son message est :" << tmpPrint[0] << " " << tmpPrint[1] << " " << tmpPrint[2] << " " << tmpPrint[3] << " " << tmpPrint[4] << " " << tmpPrint[5] << " " << tmpPrint[6] << " " << tmpPrint[7]<< " " << tmpPrint[8] << std::endl;
				//std::cout << "Ma cellule est en X " << _grid.getCell(tmpPrint[0], tmpPrint[1])->getPosition().x << " Y " << _grid.getCell(tmpPrint[0], tmpPrint[1])->getPosition().y << std::endl;
				std::cout << "tmpPrint: " << tmpPrint[0] << ", " << tmpPrint[1] << std::endl;

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
				//std::cout << "je vaic check si " << tmpPrint[0]<< "estegal a " << mapSize.x - 1 << " et " << tmpPrint[1] << " est egal a " << mapSize.y - 1 << std::endl;
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
		std::cout << "[" << GREEN << "MAP" << RESET << "] read all the queue, did not found last cell, retrying" << std::endl;
		stillCell = false;
		for (const auto &it : save) {
			if (it.getCommandName() == "bct")
				stillCell = true;
			std::cout << "il reste ça dans ma queue [" << it.getCommandName() << "]" << std::endl;
		}
		if (!stillCell) {
			_blocNumber = 0;
			_comm.writeOnServer("mct");
			std::cout << "je redemande la map" << std::endl;
		}
		_comm.setEnqueueMap(save);
		_comm.unlockMap();
		usleep(400000);
		//sleep(1);
		std::cout << "c reparti pour un tour" << std::endl;
	}
	std::cout << "je suis sorti" << std::endl;
	end = false;
	_comm.writeOnServer("sgt");
	usleep(10000);
	while (!end) {
		_comm.lockMap();
		for (const auto &it : _comm.getEnqueueMap()) {
			//	window.clear(sf::Color::Black);
			if (it.getCommandName() == "sgt") {
				_comm.setFreq(it.getCommand()[0]);
				std::cout << "[" << GREEN << "MAP" << RESET << "] retrieved frequence number " << _comm.getFreq() << std::endl;
				end = true;
				break;
			}
		}
		_comm.unlockMap();
		usleep(10000);
	}

}


void irc::ParseEnqueueMap::loadingDisplay( sf::Vector2f &mapSize, sf::RenderWindow &window)
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

void irc::ParseEnqueueMap::parseNextCommand(irc::Map &map)
{
	int i = 0;
	_comm.lockMap();
	for (const auto &it : _comm.getEnqueueMap()) {
		if (it.getCommand().empty()) {
			std::cout << "[" << RED << "MAP" << RESET << "] received empty command (command name [" << it.getCommandName() << "]" << std::endl;
			_comm.getEnqueueMap().erase(_comm.getEnqueueMap().begin());
			break;
		}
		/*std::cout << "Commande numero " << " [" << it.getCommandName() << "]" << std::endl;


		std::vector<uint> tmpCommand = it.getCommand();

		std::cout << "Player number :" << tmpCommand[0] << " Position en X " << tmpCommand[1] << " Position en Y " << tmpCommand[2] << " Orientation "  << tmpCommand[3] << " level " << tmpCommand[4] << " team name " << it.getTeamName() << std::endl;*/

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
			std::cout << "c une incantation" << std::endl;
			incantPlayer(map, it);
		} else if (it.getCommandName() == "pbc") {
			std::cout << "c un broadcast" << std::endl;
			broadcastPlayer(map, it);
		}
		_comm.getEnqueueMap().erase(_comm.getEnqueueMap().begin());

		i++;
		break;
	}
	//sleep(1);
	//	//std::cout << "il y a " << i << "messages dans ma queue "<< std::endl;

	_comm.unlockMap();
}

void irc::ParseEnqueueMap::addPlayer(irc::Map &map, const CstringArray &command)
{
	std::vector<uint> tmpCommand = command.getCommand();
	int tmpFreq = map.getComm().getFreq();

	//std::cout << "Player number :" << tmpCommand[0] << " Position en X " << tmpCommand[1] << " Position en Y " << tmpCommand[2] << " Orientation "  << tmpCommand[3] << " level " << tmpCommand[4] << " team name " << command.getTeamName() << std::endl;
	sf::Vector2f tmp = {tmpCommand[1] * 100, (tmpCommand[2] * 100)};
	//tmp.y *= -1;
	std::cout << "[" << GREEN << "MAP"<< RESET << "] adding player " << command.getCommand()[0] << " on X " << tmp.x << " Y " << tmp.y << ", on orientation " << tmpCommand[3] << " team [" << command.getTeamName() << "]" << std::endl;

//	if (tmpCommand[0] == 768 || tmpCommand[0] == 256|| tmpCommand[0] == 0 || tmpCommand[0] == 512)
//		return;
	if (command.getTeamName().empty() || map.getGrid().getTextureCharacter().empty() || tmpCommand[0] == 0) {
		std::cout << "[" << RED << "MAP" << RESET << "] Empty textureMap, not creating character :( teamName [" << command.getTeamName() << "] and id [" << tmpCommand[0] << "]" << std::endl;

	} else {
	map.getCharacterMap().emplace(tmpCommand[0], Character(map.getGrid().getTextureCharacter()[command.getTeamName()], tmp, tmpCommand[0], tmpFreq, map.getMapSize()));
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

void irc::ParseEnqueueMap::deletePlayer(irc::Map &map, const CstringArray &command)
{
	//std::cout << "je vais supprimer le joueur " << command.getCommand()[0] << std::endl;
	std::cout << "[" << GREEN << "MAP"<< RESET << "] deleting player " << command.getCommand()[0] << std::endl;
	std::map<uint, Character> &tmp = map.getCharacterMap();

	for (auto vec_it = (tmp).begin(); vec_it != (tmp).end(); ) {
		if (vec_it->second.getPlayerID() == command.getCommand()[0]) {
			tmp.erase(vec_it);
			break;
		} else {
			++vec_it;
		}
	}
}

bool irc::ParseEnqueueMap::movePlayerPosition(irc::Map &map, const CstringArray &command)
{
	sf::Vector2f tmpPos = {command.getCommand()[1] * 100, command.getCommand()[2] * 100};
//	if (command.getCommand()[0] == 768 || command.getCommand()[0] == 256|| command.getCommand()[0] == 0 || command.getCommand()[0] == 512)
//		return false;

	int tmpFreq = map.getComm().getFreq();
	std::cout << "[" << GREEN << "MAP" << RESET << "] moving player " << command.getCommand()[0] << " on X " << tmpPos.x << " Y " << tmpPos.y << std::endl;

	if (map.getCharacterMap().find((command.getCommand()[0])) == map.getCharacterMap().end()) {
		std::cout << "[" << RED << "MAP" << RESET << "] did not found player " << command.getCommand()[0] << ", exiting movePlayerPosition" << std::endl;
		return false;
	}
	map.getCharacterMap().at(command.getCommand()[0]).setPlayerMovement(tmpPos, command.getCommand()[3], tmpFreq, 7);
	return true;
}

void irc::ParseEnqueueMap::movePlayerOrientation(irc::Map &map, const CstringArray &command)
{
	if (command.getCommand()[0] == 768 || command.getCommand()[0] == 256|| command.getCommand()[0] == 0 || command.getCommand()[0] == 512)
		return;
	if (map.getCharacterMap().find((command.getCommand()[0])) == map.getCharacterMap().end()) {
		std::cout << "[" << RED << "MAP"<< RESET << "] did not found player " << command.getCommand()[0] << ", exiting movePLayerOrientation"<< std::endl;
		return;
	}
	std::cout << " je vais mettre l'orientation de mon gars en " << command.getCommand()[1] << std::endl;
	map.getCharacterMap().at(command.getCommand()[0]).setPlayerOrientation(static_cast<char>(command.getCommand()[1]), 7);
}

bool irc::ParseEnqueueMap::takeResourcePlayer(irc::Map &map, const CstringArray &command)
{
	/*std::cout << "Je vais chercher la cellule qui est en X " << command.getCommand()[0] << " X " << command.getCommand()[1] << " Y " << command.getCommand()[2] << std::endl;
	std::cout << "L'id de mon joueur " << map.getCharacterMap().at(command.getCommand()[0]).getPlayerID() << std::endl;
	std::cout << "mon joueur est en " << map.getCharacterMap().at(command.getCommand()[0]).getPlayerPosition().x << " Y " << map.getCharacterMap().at(command.getCommand()[0]).getPlayerPosition().y << std::endl;
	std::cout << "Sur la case X " << map.getCharacterMap().at(command.getCommand()[0]).getPlayerPosition().x << " Y "<< map.getCharacterMap().at(command.getCommand()[0]).getPlayerPosition().y  << " c'est la ressoucre " << command.getCommand()[1] << std::endl;*/

	if (map.getCharacterMap().find((command.getCommand()[0])) == map.getCharacterMap().end()) {
		std::cout << "[" << RED << "MAP"<< RESET << "] did not found player " << command.getCommand()[0] << ", exiting takeResourcePlayer"<< std::endl;
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


	// TODO enelever cette foret de if degueu xD

	if (command.getCommand()[1] == 6) {
		_comm._server.ressources.q0--;
		std::cout << "[" << GREEN << "PLAYER " << command.getCommand()[0] << RESET << "] took 1 resource 6" << std::endl;
	}
	else if (command.getCommand()[1] == 1) {
		_comm._server.ressources.q1--;
		std::cout << "[" << GREEN << "PLAYER " << command.getCommand()[0] << RESET << "] took 1 resource 1" << std::endl;
	}
	else if (command.getCommand()[1] == 2) {
		_comm._server.ressources.q2--;
		std::cout << "[" << GREEN << "PLAYER " << command.getCommand()[0] << RESET << "] took 1 resource 2" << std::endl;
	}
	else if (command.getCommand()[1] == 3) {
		_comm._server.ressources.q3--;
		std::cout << "[" << GREEN << "PLAYER " << command.getCommand()[0] << RESET << "] took 1 resource 3" << std::endl;
	}
	else if (command.getCommand()[1] == 4) {
		_comm._server.ressources.q4--;
		std::cout << "[" << GREEN << "PLAYER " << command.getCommand()[0] << RESET << "] took 1 resource 4" << std::endl;
	}
	else if (command.getCommand()[1] == 5) {
		_comm._server.ressources.q5--;
		std::cout << "[" << GREEN << "PLAYER " << command.getCommand()[0] << RESET << "] took 1 resource 5" << std::endl;
	}
	else if (command.getCommand()[1] == 0) {
		_comm._server.ressources.q6--;
		std::cout << "[" << GREEN << "PLAYER " << command.getCommand()[0] << RESET << "] took 1 resource 6" << std::endl;
	}
	return true;
}

bool irc::ParseEnqueueMap::dropResourcePlayer(irc::Map &map, const CstringArray &command)
{
	if (map.getCharacterMap().find((command.getCommand()[0])) == map.getCharacterMap().end()) {
		std::cout << "[" << RED << "MAP"<< RESET << "] did not found player " << command.getCommand()[0] << ", exiting dropResourcePlayer"<< std::endl;
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
	std::cout << "[" << GREEN << "PLAYER " << command.getCommand()[0] << RESET << "] dropped 1 resource on cell " << tmpX << " " << tmpY << std::endl;

	map.getGrid().getCell(tmpX, tmpY)->addRessources(command.getCommand()[1]);

	if (command.getCommand()[1] == 6) {
		_comm._server.ressources.q0++;
		std::cout << "[" << GREEN << "PLAYER " << command.getCommand()[0] << RESET << "] dropped 1 resource 6" << std::endl;
	}
	else if (command.getCommand()[1] == 1) {
		_comm._server.ressources.q1++;
		std::cout << "[" << GREEN << "PLAYER " << command.getCommand()[0] << RESET << "] dropped 1 resource 1" << std::endl;
	}
	else if (command.getCommand()[1] == 2) {
		_comm._server.ressources.q2++;
		std::cout << "[" << GREEN << "PLAYER " << command.getCommand()[0] << RESET << "] dropped 1 resource 2" << std::endl;
	}
	else if (command.getCommand()[1] == 3) {
		_comm._server.ressources.q3++;
		std::cout << "[" << GREEN << "PLAYER " << command.getCommand()[0] << RESET << "] dropped 1 resource 3" << std::endl;
	}
	else if (command.getCommand()[1] == 4) {
		_comm._server.ressources.q4++;
		std::cout << "[" << GREEN << "PLAYER " << command.getCommand()[0] << RESET << "] dropped 1 resource 4" << std::endl;
	}
	else if (command.getCommand()[1] == 5) {
		_comm._server.ressources.q5++;
		std::cout << "[" << GREEN << "PLAYER " << command.getCommand()[0] << RESET << "] dropped 1 resource 5" << std::endl;
	}
	else if (command.getCommand()[1] == 0) {
		_comm._server.ressources.q6++;
		std::cout << "[" << GREEN << "PLAYER " << command.getCommand()[0] << RESET << "] dropped 1 resource 0" << std::endl;
	}
	return true;
}

bool irc::ParseEnqueueMap::addRandomResource(irc::Map &map, const CstringArray &command)
{
	map.getGrid().getCell(command.getCommand()[0], command.getCommand()[1])->addRessources(command.getCommand()[2]);

	if (command.getCommand()[1] == 6) {
		_comm._server.ressources.q0++;
		std::cout << "[" << GREEN << "SERVER " << RESET << "] generated 1 resource 6" << std::endl;
	}
	else if (command.getCommand()[1] == 1) {
		_comm._server.ressources.q1++;
		std::cout << "[" << GREEN << "SERVER " << RESET << "] generated 1 resource 1" << std::endl;
	}
	else if (command.getCommand()[1] == 2) {
		_comm._server.ressources.q2++;
		std::cout << "[" << GREEN << "SERVER " << RESET << "] generated 1 resource 2" << std::endl;
	}
	else if (command.getCommand()[1] == 3) {
		_comm._server.ressources.q3++;
		std::cout << "[" << GREEN << "SERVER " << RESET << "] generated 1 resource 3" << std::endl;
	}
	else if (command.getCommand()[1] == 4) {
		_comm._server.ressources.q4++;
		std::cout << "[" << GREEN << "PLAYER " << RESET << "] generated 1 resource 4" << std::endl;
	}
	else if (command.getCommand()[1] == 5) {
		_comm._server.ressources.q5++;
		std::cout << "[" << GREEN << "PLAYER " << RESET << "] generated 1 resource 5" << std::endl;
	}
	else if (command.getCommand()[1] == 0) {
		_comm._server.ressources.q6++;
		std::cout << "[" << GREEN << "PLAYER " << RESET << "] generated 1 resource 0" << std::endl;
	}

	return true;
}

std::vector<std::string> &irc::ParseEnqueueMap::getTeam()
{
	std::vector<CstringArray> save;
	_comm.writeOnServer("tna");

	usleep(10000);
	std::cout << "coudzedzedcou" << std::endl;
	int i = 1;
	while (i != 0) {
		_comm.lockMap();
		save.clear();
		i = 0;
		for (const auto &it : _comm.getEnqueueMap()) {

			//	window.clear(sf::Color::Black);
			if (it.getCommandName() == "tna") {
				std::cout<< it.getTeamName() << std::endl;
				tmpTeam.push_back(it.getTeamName());
				i++;
			} else {
				save.push_back(it);
			}
			std::cout << "i vaut " << i << std::endl;
		}
		_comm.setEnqueueMap(save);
		_comm.unlockMap();
		usleep(10000);
	}
	return tmpTeam;
}

void irc::ParseEnqueueMap::incantPlayer(irc::Map &map, const CstringArray &command)
{
	sf::Vector2f tmpPos = {command.getCommand()[0], command.getCommand()[1]};
	int i = 2;
	int tmpFreq = map.getComm().getFreq();
	while (command.getCommand()[i] != 0 && i < 10) {
		std::cout << "je boucle" << std::endl;
		if (map.getCharacterMap().find((command.getCommand()[i])) == map.getCharacterMap().end()) {
			std::cout << "[" << RED << "MAP"<< RESET << "] did not found player " << command.getCommand()[i] << ", next on incantPLayer"<< std::endl;
			++i;
			continue;
		}
		std::cout << "[" << GREEN << "MAP" << RESET << "] incantation on X " << tmpPos.x << " Y " << tmpPos.y << " on player " << command.getCommand()[i] << std::endl;
		map.getCharacterMap().at(command.getCommand()[i]).setPlayerIncant(tmpFreq, 300, tmpPos);
		++i;
	}

}

void irc::ParseEnqueueMap::broadcastPlayer(irc::Map &map, const CstringArray &command)
{
	int tmpFreq = map.getComm().getFreq();
	std::cout << "je boucle" << std::endl;
	if (map.getCharacterMap().find((command.getCommand()[0])) == map.getCharacterMap().end()) {
		std::cout << "[" << RED << "MAP"<< RESET << "] did not found player " << command.getCommand()[0] << ", exit broadcastPLayer"<< std::endl;
		std::cout << "[" << GREEN << "MAP" << RESET << "] broadcast of player [" << command.getCommand()[0] << "]" << std::endl;
		map.getCharacterMap().at(command.getCommand()[0]).setPlayerBroadcast(tmpFreq, 7);
	}
}