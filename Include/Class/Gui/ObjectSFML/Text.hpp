/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Created by martin.januario@epitech.eu,
*/

#ifndef CPP_PLAZZA_TEXT_HPP
# define CPP_PLAZZA_TEXT_HPP

# include <string>
# include "AbsractObjectSFML.hpp"

namespace irc {
	class Text: public AbstractObjectSFML {
		public:
		Text(const std::string &pathFont, sf::IntRect pos, const std::string &text = "");
		~Text() = default;

		bool drawObject(sf::RenderWindow &window);
		void setPos(sf::IntRect pos);
		void setColor(sf::Color color);
		void setText(const std::string &msg);
		std::string getText() const;

		private:
		sf::Text _text;
		sf::Font _font;

		std::string _msg;
	};
}

#endif //CPP_PLAZZA_TEXT_HPP