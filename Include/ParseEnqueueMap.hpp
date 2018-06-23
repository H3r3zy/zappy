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
class ParseEnqueueMap {
	#define RED     "\x1b[31m"
	#define GREEN   "\x1b[32m"
	#define YELLOW  "\x1b[33m"
	#define BLUE    "\x1b[34m"
	#define MAGENTA "\x1b[35m"
	#define CYAN    "\x1b[36m"
	#define RESET   "\x1b[0m"

	public:
	ParseEnqueueMap(irc::Communication &comm);
	sf::Vector2f ParseMapSize();
	std::vector<std::string> &getTeam();
	void fillMap(Grid &_grid, sf::Vector2f &mapSize);
	void parseNextCommand(irc::Map &map);
	void loadingDisplay(sf::Vector2f &mapSize, sf::RenderWindow &window);

	/* Managa Game */
	void addPlayer(irc::Map &map, const CstringArray &command);
	void deletePlayer(irc::Map &map, const CstringArray &command);
	bool movePlayerPosition(irc::Map &map, const CstringArray &command);
	bool takeResourcePlayer(irc::Map &map, const CstringArray &command);
	bool dropResourcePlayer(irc::Map &map, const CstringArray &command);
	bool addRandomResource(irc::Map &map, const CstringArray &command);
	void movePlayerOrientation(irc::Map &map, const CstringArray &command);

	private:
	irc::Communication &_comm;
	std::vector<std::string> tmpTeam;
	bool _ready = false;
	int _blocNumber = 0;
};
}
#endif //CLIENT_PARSEENQUEUEMAP_HPP
