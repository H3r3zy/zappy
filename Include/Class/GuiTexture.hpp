/*
** EPITECH PROJECT, 2018
** client
** File description:
** Created by martin.januario@epitech.eu,
*/

#ifndef CLIENT_GUITEXTURE_HPP
# define CLIENT_GUITEXTURE_HPP

# include "SFML_monitor.hpp"
# include "IncludeGui.hpp"

namespace irc {

	const std::size_t WIDTH = 300;
	const std::size_t HEIGHT = 800;

	class GuiTexture {
		public:
		GuiTexture() = default;
		virtual ~GuiTexture() = default;

		void initTexture();

		protected:
		irc::SFML_monitor *_monitor = nullptr;
		std::string _nick = "Unknown";
		std::string _ip = "0.0.0.0";

		int _socketServer = 0;

		// OBJ with update
		irc::Text *_nb_teams = nullptr;
		irc::Text *_user_connected = nullptr;

		irc::Text *_nb_egg = nullptr;
		irc::Text *_nb_q0 = nullptr;
		irc::Text *_nb_q1 = nullptr;
		irc::Text *_nb_q2 = nullptr;
		irc::Text *_nb_q3 = nullptr;
		irc::Text *_nb_q4 = nullptr;
		irc::Text *_nb_q5 = nullptr;
		irc::Text *_nb_q6 = nullptr;

		private:
		void initBck();
		void initUser();
		void initSettingsGame();
		void initDataServer();
		void initDataGame();
	};

}

#endif //CLIENT_GUITEXTURE_HPP
