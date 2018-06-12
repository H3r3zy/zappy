/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Created by martin.januario@epitech.eu,
*/

#ifndef CPP_PLAZZA_CIRCLE_HPP
# define CPP_PLAZZA_CIRCLE_HPP

# include <string>
# include "AbsractObjectSFML.hpp"

namespace irc {
	class Circle : public AbstractObjectSFML {
		public:
		Circle(sf::IntRect pos, std::size_t sides = 30);
		~Circle() = default;

		bool drawObject(sf::RenderWindow &window);

		void setPos(sf::IntRect pos);
		void setColor(sf::Color color);
		void rotate(int val);

		private:
		sf::CircleShape _object;
	};
}

#endif //CPP_PLAZZA_CIRCLE_HPP
