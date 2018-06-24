/*
** EPITECH PROJECT, 2018
** PSU_ZAPPY_2017
** File description:
** Created by martin.januario@epitech.eu,
*/

#ifndef PSU_ZAPPY_2017_SPRITE_HPP
# define PSU_ZAPPY_2017_SPRITE_HPP

# include <string>
# include "AbsractObjectSFML.hpp"

namespace zap {
	class Sprite : public AbstractObjectSFML {
		public:
		Sprite(const std::string &filePath, sf::IntRect pos, const sf::IntRect &rect = {0, 0, 0, 0});
		~Sprite() = default;

		bool drawObject(sf::RenderWindow &window);

		void setPos(sf::IntRect pos);
		void setColor(sf::Color color);
		void setMirror(sf::Vector2f val);

		private:
		sf::Texture _texture;
		sf::Sprite _object;
	};
}

#endif //PSU_ZAPPY_2017_SPRITE_HPP
