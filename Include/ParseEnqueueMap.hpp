//
// EPITECH PROJECT, 2018
// ParseEnqueueMap
// File description:
// ParseEnqueMap
//

#ifndef CLIENT_PARSEENQUEUEMAP_HPP
#define CLIENT_PARSEENQUEUEMAP_HPP

#include <Class/Communication.hpp>
#include <SFML/System.hpp>
#include <unistd.h>
#include "Grid.hpp"

namespace zap {
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
	ParseEnqueueMap(zap::Communication &comm);
	sf::Vector2f ParseMapSize();
	std::vector<std::string> &getTeam();
	void fillMap(Map &map, sf::Vector2f &mapSize);
	void parseNextCommand(zap::Map &map);
	void loadingDisplay(sf::Vector2f &mapSize, sf::RenderWindow &window);

	/* Managa Game */
	void addPlayer(zap::Map &map, const CstringArray &command);
	void deletePlayer(zap::Map &map, const CstringArray &command);
	bool movePlayerPosition(zap::Map &map, const CstringArray &command);
	bool takeResourcePlayer(zap::Map &map, const CstringArray &command);
	bool dropResourcePlayer(zap::Map &map, const CstringArray &command);
	bool addRandomResource(zap::Map &map, const CstringArray &command);
	void movePlayerOrientation(zap::Map &map, const CstringArray &command);
	void incantPlayer(zap::Map &map, const CstringArray &command);
	void broadcastPlayer(zap::Map &map, const CstringArray &command);
	void endIncantation(zap::Map &map, const CstringArray &command);
	void eggDropped(zap::Map &map, const CstringArray &command);
	void eggHatching(zap::Map &map, const CstringArray &command);
	void eggHatching2(zap::Map &map, const CstringArray &command);

	private:
	zap::Communication &_comm;
	std::vector<std::string> tmpTeam;
	bool _ready = false;
	int _blocNumber = 0;
};
}
#endif //CLIENT_PARSEENQUEUEMAP_HPP
