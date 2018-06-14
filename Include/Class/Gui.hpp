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

namespace irc {

	class Gui : public irc::GuiTexture {
		public:
		Gui(int socket, std::vector<int> &listId, bool &displayGui, bool &endClient);
		~Gui();

		int initDisplayGui();
		void loopDisplay();

		protected:

		private:
		std::mutex _mutex;

		int _socketServer = 0;

		std::vector<int> &_listId; // List id to check on GUI
		bool &_displayGui; // Check if the gui is displayed
		bool &_endClient;

		bool _currentlyGuiDisplay = true;
	};
}

#endif //CLIENT_GUI_HPP
