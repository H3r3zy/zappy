/*
** EPITECH PROJECT, 2018
** client
** File description:
** Created by martin.januario@epitech.eu,
*/
#ifndef CLIENT_GUI_HPP
#define CLIENT_GUI_HPP

# include <vector>
# include <mutex>
# include "GuiTexture.hpp"
# include "Communication.hpp"

namespace irc {

	class Gui : public irc::GuiTexture {
		public:
		Gui(irc::Communication &comm, const std::string &nick, const std::string &ip, std::vector<int> &listId, bool &displayGui, bool &endClient);
		~Gui();

		int initDisplayGui();
		void loopDisplay();

		protected:

		private:
		std::mutex _mutex;

		irc::Communication &_comm;

		std::vector<int> &_listId; // List id to check on GUI
		bool &_displayGui; // Check if the gui is displayed
		bool &_endClient;

		bool _currentlyGuiDisplay = true;
	};
}

#endif //CLIENT_GUI_HPP
