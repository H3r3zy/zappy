//
// Created by wisenoa on 20/06/18.
//


#include <SFML/System.hpp>
#include "ParseEnqueueMap.hpp"
#include "Map.hpp"

ParseEnqueueMap::ParseEnqueueMap(irc::Communication &comm) : _comm(comm)
{
	_comm.writeOnServer("msz");
}

sf::Vector2f ParseEnqueueMap::ParseMapSize()
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
		std::cerr << "size: " << test.size() << std::endl;
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

void ParseEnqueueMap::fillMap(Grid &_grid, sf::Vector2f &mapSize)
{
	_comm.writeOnServer("mct");
	std::vector<CstringArray> save;

	while (true) {
		_comm.lockMap();
		std::vector<CstringArray> &test = _comm.getEnqueueMap();
		_comm.unlockMap();
		_blocNumber = 0;
		if (test.size() < mapSize.x * mapSize.y) {
			usleep(100000);
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

				/* Food */
				_grid.getCell(tmpPrint[0], tmpPrint[1])->setRessources(6, tmpPrint[8]);
				_blocNumber++;

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
		_comm.unlockMap();
		//sleep(1);
	}
}


void ParseEnqueueMap::loadingDisplay( sf::Vector2f &mapSize)
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Loading ");
	window.setPosition(sf::Vector2i(200, 100));
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
	text.setPosition(100, 0);

	while (!_ready) {
		if (_blocNumber != 0) {
			text.setString("Filling resources : " + std::to_string(_blocNumber) + " / " + total);
		} else {
			text.setString("Waiting Data response from server");

		}
		currentRect.setSize(sf::Vector2f((_blocNumber / totalNb) * 500, 50));
		window.draw(sprite);
		window.draw(totalRect);
		window.draw(currentRect);
		window.draw(text);
		window.display();
		window.clear();
	}
	window.close();
}

void ParseEnqueueMap::parseNextCommand(irc::Map &map)
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
		}
		_comm.getEnqueueMap().erase(_comm.getEnqueueMap().begin());

		i++;
		break;
	}
	//sleep(1);
	//	//std::cout << "il y a " << i << "messages dans ma queue "<< std::endl;

	_comm.unlockMap();
}

void ParseEnqueueMap::addPlayer(irc::Map &map, const CstringArray &command)
{
	//std::cout << "Commande numero " << " [" << command.getCommandName() << "]" << std::endl;

	std::vector<uint> tmpCommand = command.getCommand();

	//std::cout << "Player number :" << tmpCommand[0] << " Position en X " << tmpCommand[1] << " Position en Y " << tmpCommand[2] << " Orientation "  << tmpCommand[3] << " level " << tmpCommand[4] << " team name " << command.getTeamName() << std::endl;
	sf::Vector2f tmp = {tmpCommand[1] * 100, (tmpCommand[2] * 100)};
	//tmp.y *= -1;
	std::cout << "Je vais placer mon joueur " << tmpCommand[0] << " en X " << tmp.x << " Y " << tmp.y << std::endl;

	map.getCharacterMap().emplace(tmpCommand[0], Character(map.getGrid().getTextureCharacter(), tmp, tmpCommand[0]));
	for (auto &it : map.getCharacterMap()) {
		if (it.second.getPlayerID() == tmpCommand[0]) {
			it.second.setPlayerOrientation(static_cast<char>(tmpCommand[3]));
			it.second.setPlayerTeam(command.getTeamName());
			it.second.setPlayerLevel(tmpCommand[4]);
			break;
		}
	}
}

void ParseEnqueueMap::deletePlayer(irc::Map &map, const CstringArray &command)
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

bool ParseEnqueueMap::movePlayerPosition(irc::Map &map, const CstringArray &command)
{
	std::cout << "je vais faire bouger " << command.getCommand()[0] << std::endl;
	sf::Vector2f tmpPos = {command.getCommand()[1] * 100, command.getCommand()[2] * 100};
	//tmpPos.y *= -1;
	std::cout << "Mon joueur va bouger en X " << tmpPos.x << " Y " << tmpPos.y << std::endl;

	//	if (!map.getCharacterMap().at(command.getCommand()[0]).getAction()) {
		map.getCharacterMap().at(command.getCommand()[0]).setPlayerMovement(tmpPos, command.getCommand()[3]);
		return true;
//	} else {
///		return false;
//	}
	//map.getCharacterMap()[0].setPlayerMovement(tmpPos, command.getCommand()[3]);
}

void ParseEnqueueMap::movePlayerOrientation(irc::Map &map, const CstringArray &command)
{
	std::cout << " je vais mettre l'orientation de mon gars en " << command.getCommand()[1] << std::endl;
	map.getCharacterMap().at(command.getCommand()[0]).setPlayerOrientation(static_cast<char>(command.getCommand()[1]));
}

// pmv // ID posX posY orientation
// lautre // ID orientation