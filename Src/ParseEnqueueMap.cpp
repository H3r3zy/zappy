//
// Created by wisenoa on 20/06/18.
//


#include <SFML/System.hpp>
#include "ParseEnqueueMap.hpp"

ParseEnqueueMap::ParseEnqueueMap(irc::Communication &comm) : _comm(comm)
{
	_comm.writeOnServer("msz");
}

sf::Vector2f ParseEnqueueMap::ParseMapSize()
{
	sf::Vector2f tmpMap = {0, 0};
	while (true) {
		_comm.lockMap();
		std::vector<CstringArray> test = _comm.getEnqueueMap();
		_comm.unlockMap();
		for (const auto &it : test) {
			std::cout << "Coammnde Name [" << it.getCommandName() << "]" << std::endl;
			auto tmpPrint = it.getCommand();
			if (tmpPrint.size() == 8)
				std::cout << "Et son message est :"
					<< tmpPrint[0] << " " << tmpPrint[1]
					<< " " << tmpPrint[2] << " "
					<< tmpPrint[3] << " " << tmpPrint[4]
					<< " " << tmpPrint[5] << " "
					<< tmpPrint[6] << " " << tmpPrint[7]
					<< std::endl;

			if (it.getCommandName() == "msz") {
				tmpMap.x = tmpPrint[0];
				tmpMap.y = tmpPrint[1];
				std::cout << "je vais return un vector X" << tmpMap.x << " Y " << tmpMap.y << std::endl;
				_comm.lockMap();
				// TODO delete node
				_comm.unlockMap();
				return tmpMap;
			}
		}
	}
}

void ParseEnqueueMap::fillMap(Grid &_grid, sf::Vector2f &mapSize)
{
	_comm.writeOnServer("mct");

	while (true) {
		_comm.lockMap();
		std::vector<CstringArray> test = _comm.getEnqueueMap();
		_comm.unlockMap();
		_blocNumber = 0;
		for (const auto &it : test) {
		//	window.clear(sf::Color::Black);
			if (it.getCommandName() == "bct") {
				std::cout << "Coammnde Name [" << it.getCommandName() << "]" << std::endl;
				auto tmpPrint = it.getCommand();
				if (tmpPrint.size() == 9)
					std::cout << "Et son message est :" << tmpPrint[0] << " " << tmpPrint[1] << " " << tmpPrint[2] << " " << tmpPrint[3] << " " << tmpPrint[4] << " " << tmpPrint[5] << " " << tmpPrint[6] << " " << tmpPrint[7]<< " " << tmpPrint[8] << std::endl;
				std::cout << "Ma cellule est en X " << _grid.getCell(tmpPrint[0], tmpPrint[1])->getPosition().x << " Y " << _grid.getCell(tmpPrint[0], tmpPrint[1])->getPosition().y << std::endl;

				/* Food */
				_grid.getCell(tmpPrint[0], tmpPrint[1])->setRessources(0, tmpPrint[2]);

				/* Q1 => Q6 */
				_grid.getCell(tmpPrint[0], tmpPrint[1])->setRessources(1, tmpPrint[3]);
				_grid.getCell(tmpPrint[0], tmpPrint[1])->setRessources(2, tmpPrint[4]);
				_grid.getCell(tmpPrint[0], tmpPrint[1])->setRessources(3, tmpPrint[5]);

				_grid.getCell(tmpPrint[0], tmpPrint[1])->setRessources(4, tmpPrint[6]);
				_grid.getCell(tmpPrint[0], tmpPrint[1])->setRessources(5, tmpPrint[7]);
				_grid.getCell(tmpPrint[0], tmpPrint[1])->setRessources(6, tmpPrint[8]);
				_blocNumber++;

				if (tmpPrint[0] == mapSize.x - 1 && tmpPrint[1] == mapSize.y - 1) {
					_ready = true;
					return;
				}
			}
		}
		//sleep(1);
	}
}


void ParseEnqueueMap::loadingDisplay( sf::Vector2f &mapSize)
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Loading");
	sf::Text text;
	sf::Font font;
	std::string total = std::to_string(mapSize.x * mapSize.y);

	font.loadFromFile("arial.ttf");
	text.setFont(font);


	while (!_ready) {
		std::cout << "bloc :" << _blocNumber << " total " << total << std::endl;
		text.setString("Loading : " + std::to_string(_blocNumber) + " / " + total);
		window.draw(text);
		window.display();
		window.clear();
	}
	window.close();
}