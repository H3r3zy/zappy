/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Created by martin.januario@epitech.eu,
*/

#ifndef CPP_PLAZZA_SQUARE_HPP
# define CPP_PLAZZA_SQUARE_HPP

# include <string>
# include "AbsractObjectSFML.hpp"

namespace irc {
	class Square : public AbstractObjectSFML {
		public:
		Square(sf::IntRect pos);
		~Square() = default;

		bool drawObject(sf::RenderWindow &window);

		void setPos(sf::IntRect pos);
		void setColor(sf::Color color);

		private:
		sf::RectangleShape _object;
	};
}

#endif //CPP_PLAZZA_SQUARE_HPP
