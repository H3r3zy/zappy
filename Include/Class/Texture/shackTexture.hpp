/*
** EPITECH PROJECT, 2018
** client
** File description:
** Created by martin.januario@epitech.eu,
*/

#ifndef CLIENT_SHACKTEXTURE_HPP
# define CLIENT_SHACKTEXTURE_HPP

# include "CstringArray.hpp"
# include "IncludeGui.hpp"

namespace zap {

	class Gui;

	class shackTexture {
		public:
		shackTexture(zap::Gui &base);
		~shackTexture() = default;

		void initTexture();
		protected:
		void updateShack();

		private:
		void initBck();
		void initHeader();
		void initNbPlayer();
		void initData();
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

		zap::Text *_nb_player = nullptr;
		zap::Text *_nickShack = nullptr;

	};

}

#endif //CLIENT_SHACKTEXTURE_HPP
