//
// Created by wisenoa on 20/06/18.
//

#include <SFML/System.hpp>
#include "ParseEnqueueMap.hpp"

ParseEnqueueMap::ParseEnqueueMap(irc::Communication &comm) : _comm(comm)
{
	std::cout << "coucou" << std::endl;
	_comm.writeOnServer("msz");
}

sf::Vector2f ParseEnqueueMap::ParseMapSize()
{
	sf::Vector2f tmpMap = {0, 0};
	while (true) {
		_comm.lockMap();
		std::vector<CstringArray> test = _comm.getEnqueueMap();
		_comm.unlockMap();
//		std::cerr << "SIZE: " << test.size() << std::endl;
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
				return tmpMap;
			}
		}
	}

}
