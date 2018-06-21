/*
** EPITECH PROJECT, 2018
** client
** File description:
** Created by martin.januario@epitech.eu,
*/

#ifndef CLIENT_MAP_HPP
# define CLIENT_MAP_HPP

# include <string>
# include <vector>
# include <iostream>
# include <SFML/System.hpp>
# include <SFML/Graphics/RenderWindow.hpp>
# include <SFML/Window/Event.hpp>
# include "ParseEnqueueMap.hpp"
# include "Grid.hpp"
# include "WindowInfo.hpp"
# include "Character.hpp"
# include "Communication.hpp"

namespace irc {

	enum {
		MAP,
		MINIMAP,
		HUD
	};

	class Map {
		public:
		Map(irc::Communication &comm, bool &displayGui, bool &endClient);
		~Map() = default;

		void loopDisplay();
		std::vector<Character> &getCharacterMap();
		Grid &getGrid();


		private:
		irc::Communication &_comm;

		bool &_displayGui; // Check if the gui is displayed
		bool &_endClient;

		bool getEvent();
		void initCamera();

		/* SFML */
		sf::Event _event;
		sf::RectangleShape _playerPos;
		/* std::pair<Global camera, Minimap camera > */
		std::vector<sf::View> _camera;
		sf::RenderWindow _gameWindow;

		/* Member Classes */
		WindowInfo *_windowInfo;
		std::vector<Character> _character;
		ParseEnqueueMap _enqueueMap;
		sf::Vector2f _mapSize = {10, 10};
		Grid _grid;

	};
}

#endif //CLIENT_MAP_HPP
