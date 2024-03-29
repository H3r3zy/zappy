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

namespace zap {

	enum {
		MAP,
		MINIMAP,
		HUD
	};

	class Map {
		public:
		Map(zap::Communication &comm, bool &displayGui, bool &endClient);
		~Map() = default;

		void loopDisplay();
		void updateGuiData();
		std::map<uint, Character> &getCharacterMap();
		Grid &getGrid();
		zap::Communication &getComm();
		const sf::Vector2f &getMapSize() const;
		const std::vector<std::string> &getTeamName() const;
		std::map<int, std::pair<std::string, sf::Vector2i>> &getEggMap();

		private:
		zap::Communication &_comm;

		bool &_displayGui; // Check if the gui is displayed
		bool &_endClient;

		bool getEvent();
		void initCamera();
		void initColorTeam();

		/* SFML */
		sf::Event _event;
		sf::RectangleShape _playerPos;
		/* std::pair<Global camera, Minimap camera > */
		std::vector<sf::View> _camera;
		sf::RenderWindow _gameWindow;

		/* Member Classes */
		WindowInfo *_windowInfo;
		std::map<uint, Character> _character;
		ParseEnqueueMap _enqueueMap;
		sf::Vector2f _mapSize = {10, 10};
		std::vector<std::string> _teamName;
		std::map<std::string, sf::Color> _teamColor;
		Grid _grid;
		std::map<int, std::pair<std::string, sf::Vector2i>> _egg;
	};
}

#endif //CLIENT_MAP_HPP
