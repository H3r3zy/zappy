//
// Created by wisenoa on 20/06/18.
//


#ifndef CLIENT_PARSEENQUEUEMAP_HPP
#define CLIENT_PARSEENQUEUEMAP_HPP

#include <Class/Communication.hpp>
#include <SFML/System.hpp>
#include <unistd.h>
#include "Grid.hpp"

namespace irc {
	class Map;
}

class ParseEnqueueMap {
	public:
	ParseEnqueueMap(irc::Communication &comm);
	sf::Vector2f ParseMapSize();
	void fillMap(Grid &_grid, sf::Vector2f &mapSize);
	void parseNextCommand(irc::Map &map);
	void loadingDisplay(sf::Vector2f &mapSize);

	/* Managa Game */
	void addPlayer(irc::Map &map, const CstringArray &command);
	void deletePlayer(irc::Map &map, const CstringArray &command);
	bool movePlayerPosition(irc::Map &map, const CstringArray &command);
	void movePlayerOrientation(irc::Map &map, const CstringArray &command);

	private:
	irc::Communication &_comm;
	bool _ready = false;
	int _blocNumber = 0;
};

#endif //CLIENT_PARSEENQUEUEMAP_HPP
