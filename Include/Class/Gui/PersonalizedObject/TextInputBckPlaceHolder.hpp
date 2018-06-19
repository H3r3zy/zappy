/*
** EPITECH PROJECT, 2018
** client
** File description:
** Created by martin.januario@epitech.eu,
*/

#ifndef CLIENT_TEXTINPUTBCKPLACEHOLDER_HPP
# define CLIENT_TEXTINPUTBCKPLACEHOLDER_HPP

#include "IncludeGui.hpp"

namespace irc {

	class TextInputBckPlaceHorder {
		public:

		static irc::Container *createInput(const sf::IntRect &pos, const std::string &placeholder, const std::string &font, int fontSize = 10);

		private:
		TextInputBckPlaceHorder() = default;

		// method
		static void inputTextWrite(irc::IObjectSFML *placeholder, irc::IObjectSFML *input_obj, bool layer);
	};

}

#endif //CLIENT_TEXTINPUTBCKPLACEHOLDER_HPP
