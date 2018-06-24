/*
** EPITECH PROJECT, 2018
** PSU_ZAPPY_2017
** File description:
** Created by martin.januario@epitech.eu,
*/

#ifndef PSU_ZAPPY_2017_SQUARE_HPP
# define PSU_ZAPPY_2017_SQUARE_HPP

# include <string>
# include "AbsractObjectSFML.hpp"

namespace zap {
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

#endif //PSU_ZAPPY_2017_SQUARE_HPP
