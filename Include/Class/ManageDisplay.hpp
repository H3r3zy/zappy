/*
** EPITECH PROJECT, 2018
** client
** File description:
** Created by martin.januario@epitech.eu,
*/

#ifndef CLIENT_MANAGEDISPLAY_HPP
# define CLIENT_MANAGEDISPLAY_HPP

# include <vector>
# include <string>
# include <SFML/Audio.hpp>
# include "Map.hpp"
# include "Gui.hpp"
# include "Thread.hpp"
# include "Communication.hpp"

namespace irc {

	class ManageDisplay {
		public:
		ManageDisplay(int socketServer, const std::string &nick, const std::string &ip, sf::Music &music);
		~ManageDisplay();

		protected:
		int _socketServer = 0;

		private:
		bool _displayGui = true; // Check if the gui is displayed
		bool _endClient = false;

		sf::Music &_music;

		irc::Communication _comm;

		my::Thread *_thread = nullptr;
		my::Thread *_threadRead = nullptr;

		irc::Map _map;
		irc::Gui _gui;

		std::string _nick;
	};

}

#endif //CLIENT_MANAGEDISPLAY_HPP
