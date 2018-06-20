/*
** EPITECH PROJECT, 2018
** client
** File description:
** Created by martin.januario@epitech.eu,
*/

#ifndef CLIENT_SHACKTEXTURE_HPP
# define CLIENT_SHACKTEXTURE_HPP

# include "IncludeGui.hpp"

namespace irc {

	class Gui;

	class shackTexture {
		public:
		shackTexture(irc::Gui &base);
		~shackTexture() = default;

		void initTexture();
		protected:

		private:
		void initBck();
		void initHeader();
		void initNbPlayer();
		void initData();
		void initArrow();
		void initClose();

		irc::Gui &_base;

		irc::Text *_nb_egg = nullptr;
		irc::Text *_nb_q0 = nullptr;
		irc::Text *_nb_q1 = nullptr;
		irc::Text *_nb_q2 = nullptr;
		irc::Text *_nb_q3 = nullptr;
		irc::Text *_nb_q4 = nullptr;
		irc::Text *_nb_q5 = nullptr;
		irc::Text *_nb_q6 = nullptr;

		irc::Text *_nb_player = nullptr;
		irc::Text *_nickShack = nullptr;

	};

}

#endif //CLIENT_SHACKTEXTURE_HPP
