/*
** EPITECH PROJECT, 2018
** client
** File description:
** Created by martin.januario@epitech.eu,
*/

#ifndef CLIENT_IATEXTURE_HPP
# define CLIENT_IATEXTURE_HPP

# include "IncludeGui.hpp"

namespace zap {

	class Gui;

	class IATexture {
		public:
		IATexture(zap::Gui &base);
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

		zap::Gui &_base;

		zap::Text *_nb_q0 = nullptr;
		zap::Text *_nb_q1 = nullptr;
		zap::Text *_nb_q2 = nullptr;
		zap::Text *_nb_q3 = nullptr;
		zap::Text *_nb_q4 = nullptr;
		zap::Text *_nb_q5 = nullptr;
		zap::Text *_nb_q6 = nullptr;

		zap::Text *_nickIA = nullptr;
		zap::Text *_status = nullptr;
		zap::Text *_pos = nullptr;
		zap::Text *_team = nullptr;

		std::vector<zap::Sprite *> _icon_team;

	};

}

#endif //CLIENT_IATEXTURE_HPP
