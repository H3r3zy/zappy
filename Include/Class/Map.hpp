/*
** EPITECH PROJECT, 2018
** client
** File description:
** Created by martin.januario@epitech.eu,
*/

#ifndef CLIENT_MAP_HPP
# define CLIENT_MAP_HPP

namespace irc {

	class Map {
		public:
		Map();
		~Map() = default;

		void loopDisplay();

		protected:

		private:
		int _socket = 0;
	};
}

#endif //CLIENT_MAP_HPP
