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

	const std::size_t WIDTH = 500;
	const std::size_t HEIGHT = 800;

	class GuiTexture {
		public:
		GuiTexture() = default;
		virtual ~GuiTexture() = default;

		void initTexture();

		protected:
		irc::SFML_monitor *_monitor = nullptr;

		private:
	};

}

#endif //CLIENT_GUITEXTURE_HPP
