//
// Created by wisenoa on 20/06/18.
//


#ifndef CLIENT_PARSEENQUEUEMAP_HPP
#define CLIENT_PARSEENQUEUEMAP_HPP

#include <Class/Communication.hpp>
#include <SFML/System.hpp>
#include <unistd.h>
#include "Grid.hpp"

class ParseEnqueueMap {
	public:
	ParseEnqueueMap(irc::Communication &comm);
	sf::Vector2f ParseMapSize();
	void fillMap(Grid &_grid);

	private:
	irc::Communication &_comm;
};

#endif //CLIENT_PARSEENQUEUEMAP_HPP
