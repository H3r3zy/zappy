/*
** EPITECH PROJECT, 2018
** client
** File description:
** Created by martin.januario@epitech.eu,
*/

#ifndef CLIENT_IATEXTURE_HPP
# define CLIENT_IATEXTURE_HPP

# include "IncludeGui.hpp"

namespace irc {

	class Gui;

	class IATexture {
		public:
		IATexture(irc::Gui &base);
		~IATexture() = default;

		void initTexture();
		protected:
		void updateIAData();

		private:
		void initBck();
		void initUser();
		void initDataServer();
		void initDataGame();

		void initArrow();
		void initClose();

		irc::Gui &_base;

		irc::Text *_nb_q0 = nullptr;
		irc::Text *_nb_q1 = nullptr;
		irc::Text *_nb_q2 = nullptr;
		irc::Text *_nb_q3 = nullptr;
		irc::Text *_nb_q4 = nullptr;
		irc::Text *_nb_q5 = nullptr;
		irc::Text *_nb_q6 = nullptr;

		irc::Text *_nickIA = nullptr;
		irc::Text *_status = nullptr;
		irc::Text *_pos = nullptr;
		irc::Text *_team = nullptr;

		std::vector<irc::Sprite *> _icon_team;

	};

}

#endif //CLIENT_IATEXTURE_HPP
