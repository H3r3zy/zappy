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
		if (test.size() < mapSize.x * mapSize.y) {
			usleep(100000);
			continue;
		}
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