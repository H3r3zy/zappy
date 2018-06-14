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

namespace irc {

	class Map {
		public:
		Map(int socket, std::vector<int> &listId, bool &displayGui, bool &endClient);
		~Map() = default;

		void loopDisplay();

		protected:

		private:

		int _socketServer = 0;

		std::vector<int> &_listId; // List id to check on GUI
		bool &_displayGui; // Check if the gui is displayed
		bool &_endClient;

	};
}

#endif //CLIENT_MAP_HPP
