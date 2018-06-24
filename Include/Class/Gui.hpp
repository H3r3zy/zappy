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
# include <SFML/Audio.hpp>
# include "GuiTexture.hpp"
# include "shackTexture.hpp"
# include "IATexture.hpp"
# include "Communication.hpp"

namespace zap {

	class Gui : public zap::GuiTexture, public zap::shackTexture, public zap::IATexture {
		public:
		Gui(zap::Communication &comm, const std::string &nick, const std::string &ip, bool &displayGui, bool &endClient, sf::Music &music);
		~Gui();

		int initDisplayGui();
		void loopDisplay();
		void addGenericFunction(int scene);

		zap::Communication &_comm;
		sf::Music &_music;

		zap::SFML_monitor *_monitor = nullptr;

		bool &_displayGui; // Check if the gui is displayed
		bool &_endClient;
		protected:

		private:
		std::mutex _mutex;
	};
}

#endif //CLIENT_GUI_HPP
