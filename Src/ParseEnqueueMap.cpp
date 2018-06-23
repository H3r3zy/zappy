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
	usleep(100000);
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

void irc::ParseEnqueueMap::fillMap(Grid &_grid, sf::Vector2f &mapSize)
{
	_comm.writeOnServer("mct");
	std::vector<CstringArray> save;

	while (true) {
		_comm.lockMap();
		std::cerr << "FILLMAP" << std::endl;
		std::vector<CstringArray> &test = _comm.getEnqueueMap();
		_comm.unlockMap();
		_blocNumber = 0;
		std::cout << "Je vais afficher ma map" << std::endl;
		for (const auto &it: test) {
			std::cout << "jai recu " << it.getCommand()[0] << " " << it.getCommand()[1] << std::endl;
		}
		std::cout << "jai finit" << std::endl;
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
				if (tmpPrint.size() == 9)
					//std::cout << "Et son message est :" << tmpPrint[0] << " " << tmpPrint[1] << " " << tmpPrint[2] << " " << tmpPrint[3] << " " << tmpPrint[4] << " " << tmpPrint[5] << " " << tmpPrint[6] << " " << tmpPrint[7]<< " " << tmpPrint[8] << std::endl;
				//std::cout << "Ma cellule est en X " << _grid.getCell(tmpPrint[0], tmpPrint[1])->getPosition().x << " Y " << _grid.getCell(tmpPrint[0], tmpPrint[1])->getPosition().y << std::endl;


				/* Q1 => Q6 */
				_grid.getCell(tmpPrint[0], tmpPrint[1])->setRessources(0, tmpPrint[2]);
				_grid.getCell(tmpPrint[0], tmpPrint[1])->setRessources(1, tmpPrint[3]);
				_grid.getCell(tmpPrint[0], tmpPrint[1])->setRessources(2, tmpPrint[4]);
				_grid.getCell(tmpPrint[0], tmpPrint[1])->setRessources(3, tmpPrint[5]);
				_grid.getCell(tmpPrint[0], tmpPrint[1])->setRessources(4, tmpPrint[6]);
				_grid.getCell(tmpPrint[0], tmpPrint[1])->setRessources(5, tmpPrint[7]);
				_grid.getCell(tmpPrint[0], tmpPrint[1])->setRessources(6, tmpPrint[8]);


				_comm._server.ressources.q6 += tmpPrint[2];

				_comm._server.ressources.q1 += tmpPrint[3];
				_comm._server.ressources.q2 += tmpPrint[4];
				_comm._server.ressources.q3 += tmpPrint[5];

				_comm._server.ressources.q4 += tmpPrint[6];
				_comm._server.ressources.q5 += tmpPrint[7];
				_comm._server.ressources.q0 += tmpPrint[8];


				/* Food */
				_blocNumber++;
				std::cout << "je vaic check si " << tmpPrint[0]<< "estegal a " << mapSize.x - 1 << " et " << tmpPrint[1] << " est egal a " << mapSize.y - 1 << std::endl;
				if (tmpPrint[0] == mapSize.x - 1 && tmpPrint[1] == mapSize.y - 1) {
					_ready = true;
					_comm.setEnqueueMap(save);
					_comm.unlockMap();
					return;
				}
			} else {
				save.push_back(it);
			}
		}
		std::cout << "[" << GREEN << "MAP" << RESET << "] read all the queue, did not found last cell, retrying" << std::endl;

		_comm.unlockMap();
		//sleep(1);
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

	sf::RectangleShape totalRect;
	totalRect.setFillColor(sf::Color(0, 80, 0, 122));
	totalRect.setSize(sf::Vector2f(500, 50));
	totalRect.setPosition(100, 540);

	sf::RectangleShape currentRect;
	currentRect.setFillColor(sf::Color::Green);
	currentRect.setSize(sf::Vector2f(0, 50));
	currentRect.setPosition(100, 540);

	texture.loadFromFile("ronflex.png");
	sprite.setTexture(texture);

	font.loadFromFile("pokemon.ttf");
	text.setFont(font);
	text.setCharacterSize(20);

	while (!_ready) {
		if (_blocNumber != 0) {
			text.setString("Filling resources : " + std::to_string(_blocNumber) + " / " + total);
		} else {
			text.setString("Waiting Data response from server (Current data send :" + std::to_string(_comm.getEnqueueMap().size()) + ")");

		}
		currentRect.setSize(sf::Vector2f((_blocNumber / totalNb) * 500, 50));
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
	std::cout << "Commande numero " << " [" << command.getCommandName() << "]" << std::endl;

	std::vector<uint> tmpCommand = command.getCommand();

	//std::cout << "Player number :" << tmpCommand[0] << " Position en X " << tmpCommand[1] << " Position en Y " << tmpCommand[2] << " Orientation "  << tmpCommand[3] << " level " << tmpCommand[4] << " team name " << command.getTeamName() << std::endl;
	sf::Vector2f tmp = {tmpCommand[1] * 100, (tmpCommand[2] * 100)};
	//tmp.y *= -1;
	std::cout << "Je vais placer mon joueur " << tmpCommand[0] << " en X " << tmp.x << " Y " << tmp.y << std::endl;
	std::cout << "orientation "<< tmpCommand[3] << " team player " << command.getTeamName() << " player level " << tmpCommand[4] << std::endl;
	if (tmpCommand[0] == 768 || tmpCommand[0] == 256|| tmpCommand[0] == 0 || tmpCommand[0] == 512)
		return;
	map.getCharacterMap().emplace(tmpCommand[0], Character(map.getGrid().getTextureCharacter()[command.getTeamName()], tmp, tmpCommand[0]));
	for (auto &it : map.getCharacterMap()) {
		if (it.second.getPlayerID() == tmpCommand[0]) {
			it.second.setPlayerOrientation(static_cast<char>(tmpCommand[3]));
			it.second.setPlayerTeam(command.getTeamName());
			it.second.setPlayerLevel(tmpCommand[4]);
			break;
		}
	}
}

void irc::ParseEnqueueMap::deletePlayer(irc::Map &map, const CstringArray &command)
{
	//std::cout << "je vais supprimer le joueur " << command.getCommand()[0] << std::endl;
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
	std::cout << "je vais faire bouger " << command.getCommand()[0] << std::endl;
	sf::Vector2f tmpPos = {command.getCommand()[1] * 100, command.getCommand()[2] * 100};
	//tmpPos.y *= -1;
	std::cout << "Mon joueur va bouger en X " << tmpPos.x << " Y " << tmpPos.y << std::endl;
	if (command.getCommand()[0] == 768 || command.getCommand()[0] == 256|| command.getCommand()[0] == 0 || command.getCommand()[0] == 512)
		return false;

	//	if (!map.getCharacterMap().at(command.getCommand()[0]).getAction()) {
		map.getCharacterMap().at(command.getCommand()[0]).setPlayerMovement(tmpPos, command.getCommand()[3]);
		return true;
//	} else {
///		return false;
//	}
	//map.getCharacterMap()[0].setPlayerMovement(tmpPos, command.getCommand()[3]);
}

void irc::ParseEnqueueMap::movePlayerOrientation(irc::Map &map, const CstringArray &command)
{
	if (command.getCommand()[0] == 768 || command.getCommand()[0] == 256|| command.getCommand()[0] == 0 || command.getCommand()[0] == 512)
		return;
	std::cout << " je vais mettre l'orientation de mon gars en " << command.getCommand()[1] << std::endl;
	map.getCharacterMap().at(command.getCommand()[0]).setPlayerOrientation(static_cast<char>(command.getCommand()[1]));
}

bool irc::ParseEnqueueMap::takeResourcePlayer(irc::Map &map, const CstringArray &command)
{
	/*std::cout << "Je vais chercher la cellule qui est en X " << command.getCommand()[0] << " X " << command.getCommand()[1] << " Y " << command.getCommand()[2] << std::endl;
	std::cout << "L'id de mon joueur " << map.getCharacterMap().at(command.getCommand()[0]).getPlayerID() << std::endl;
	std::cout << "mon joueur est en " << map.getCharacterMap().at(command.getCommand()[0]).getPlayerPosition().x << " Y " << map.getCharacterMap().at(command.getCommand()[0]).getPlayerPosition().y << std::endl;
	std::cout << "Sur la case X " << map.getCharacterMap().at(command.getCommand()[0]).getPlayerPosition().x << " Y "<< map.getCharacterMap().at(command.getCommand()[0]).getPlayerPosition().y  << " c'est la ressoucre " << command.getCommand()[1] << std::endl;*/
	map.getCharacterMap().at(command.getCommand()[0]).setPlayerTake((char)command.getCommand()[1], command.getCommand()[1]);
	map.getGrid().getCell(static_cast<int>(map.getCharacterMap().at(command.getCommand()[0]).getPlayerPosition().x / 100), static_cast<int>(map.getCharacterMap().at(command.getCommand()[0]).getPlayerPosition().y / 100))->delResources(command.getCommand()[1]);


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
	map.getCharacterMap().at(command.getCommand()[0]).setPlayerTake((char)command.getCommand()[1], command.getCommand()[1]);
	map.getGrid().getCell(static_cast<int>(map.getCharacterMap().at(command.getCommand()[0]).getPlayerPosition().x / 100), static_cast<int>(map.getCharacterMap().at(command.getCommand()[0]).getPlayerPosition().y / 100))->addRessources(command.getCommand()[1]);

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
	std::cout << "size " << command.getCommand().size() << std::endl;
	std::cout << "ma celle est cencee etre en " << command.getCommand()[0] << " " << command.getCommand()[1] << std::endl;
	std::cout << "je vais add une random ressource " << command.getCommand()[2] << std::endl;
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

	usleep(100000);
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
		usleep(100000);
	}
	return tmpTeam;
}