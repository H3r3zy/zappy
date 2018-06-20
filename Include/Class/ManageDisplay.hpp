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
# include "Map.hpp"
# include "Gui.hpp"
# include "Thread.hpp"
# include "Communication.hpp"

namespace irc {

	class ManageDisplay {
		public:
		ManageDisplay(int socketServer, const std::string &nick = "Unknown", const std::string &ip = "0.0.0.0");
		~ManageDisplay();

		protected:
		int _socketServer = 0;

		private:
		bool _displayGui = true; // Check if the gui is displayed
		bool _endClient = false;

		irc::Communication _comm;

		irc::Map _map;
		irc::Gui _gui;

		my::Thread *_thread = nullptr;
		my::Thread *_threadRead = nullptr;


		std::string _nick;
	};

}

#endif //CLIENT_MANAGEDISPLAY_HPP
