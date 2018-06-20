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


		private:
		irc::Communication &_comm;

		bool &_displayGui; // Check if the gui is displayed
		bool &_endClient;

		bool getEvent();
		void initCamera();
		sf::Vector2f _mapSize = {50, 50};

		/* SFML */
		sf::Event _event;
		sf::RectangleShape _playerPos;
		/* std::pair<Global camera, Minimap camera > */
		std::vector<sf::View> _camera;
		sf::RenderWindow _gameWindow;

		/* Member Classes */
		Grid _grid;
		WindowInfo *_windowInfo;
		std::vector<Character> _character;

	};
}

#endif //CLIENT_MAP_HPP
