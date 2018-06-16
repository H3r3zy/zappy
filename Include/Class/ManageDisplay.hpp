/*
** EPITECH PROJECT, 2018
** client
** File description:
** Created by martin.januario@epitech.eu,
*/

#ifndef CLIENT_MANAGEDISPLAY_HPP
# define CLIENT_MANAGEDISPLAY_HPP

# include <vector>
# include "Map.hpp"
# include "Gui.hpp"
# include "Thread.hpp"

namespace irc {

	class ManageDisplay {
		public:
		ManageDisplay(int socketServerMap, int socketServerGui, const std::string &nick = "Unknown", const std::string &ip = "0.0.0.0");
		~ManageDisplay();

		protected:
		int _socketServerMap = 0;
		int _socketServerGui = 0;

		private:
		std::vector<int> _listId; // List id to check on GUI
		bool _displayGui = true; // Check if the gui is displayed
		bool _endClient = false;

		irc::Map _map;
		irc::Gui _gui;

		my::Thread *_thread = nullptr;
		std::string _nick;
	};

}

#endif //CLIENT_MANAGEDISPLAY_HPP
