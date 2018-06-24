/*
** EPITECH PROJECT, 2018
** PSU_ZAPPY_2017
** File description:
** Created by martin.januario@epitech.eu,
*/

#ifndef PSU_ZAPPY_2017_CIRCLE_HPP
# define PSU_ZAPPY_2017_CIRCLE_HPP

# include <string>
# include "AbsractObjectSFML.hpp"

namespace zap {
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

#endif //PSU_ZAPPY_2017_CIRCLE_HPP
