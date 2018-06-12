/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Created by martin.januario@epitech.eu,
*/

#ifndef CPP_PLAZZA_SPRITE_HPP
# define CPP_PLAZZA_SPRITE_HPP

# include <string>
# include "AbsractObjectSFML.hpp"

namespace irc {
	class Sprite : public AbstractObjectSFML {
		public:
		Sprite(const std::string &filePath, sf::IntRect pos);
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

#endif //CPP_PLAZZA_SPRITE_HPP
