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

namespace zap {

	class Gui;

	class GuiTexture {
		public:
		GuiTexture(zap::Gui &base);
		virtual ~GuiTexture() = default;

		void initTexture();

		protected:
		void updateServerData();

		zap::Gui &_base;

		std::string _nick = "Unknown";
		std::string _ip = "0.0.0.0";

		int _socketServer = 0;

		// OBJ with update
		zap::Text *_nb_teams = nullptr;
		zap::Text *_user_connected = nullptr;
		zap::Text *_actual_frequency = nullptr;

		private:
		void initBck();
		void initUser();
		void initSettingsGame();
		void initDataServer();
		void initDataGame();
		void initSounds();

		zap::Text *_nb_egg = nullptr;
		zap::Text *_nb_q0 = nullptr;
		zap::Text *_nb_q1 = nullptr;
		zap::Text *_nb_q2 = nullptr;
		zap::Text *_nb_q3 = nullptr;
		zap::Text *_nb_q4 = nullptr;
		zap::Text *_nb_q5 = nullptr;
		zap::Text *_nb_q6 = nullptr;

	};

}

#endif //CLIENT_GUITEXTURE_HPP
