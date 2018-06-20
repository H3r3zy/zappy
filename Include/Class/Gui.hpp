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
# include "shackTexture.hpp"
# include "IATexture.hpp"
# include "Communication.hpp"

namespace irc {

	class Gui : public irc::GuiTexture, public irc::shackTexture, public irc::IATexture {
		public:
		Gui(irc::Communication &comm, const std::string &nick, const std::string &ip, bool &displayGui, bool &endClient);
		~Gui();

		int initDisplayGui();
		void loopDisplay();
		void addGenericFunction(int scene);

		irc::Communication &_comm;
		irc::SFML_monitor *_monitor = nullptr;

		bool &_displayGui; // Check if the gui is displayed
		bool &_endClient;
		protected:

		private:
		std::mutex _mutex;
	};
}

#endif //CLIENT_GUI_HPP
