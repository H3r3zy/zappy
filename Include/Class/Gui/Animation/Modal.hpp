/*
** EPITECH PROJECT, 2018
** PSU_ZAPPY_2017
** File description:
** Created by martin.januario@epitech.eu,
*/

#ifndef PSU_ZAPPY_2017_MODAL_HPP
# define PSU_ZAPPY_2017_MODAL_HPP

# include "AbsractObjectSFML.hpp"

namespace zap {
	class Modal : public AbstractObjectSFML {
		public:
		Modal(IObjectSFML *, sf::Vector2i to, std::size_t timeElapsed);
		~Modal();

		bool drawObject(sf::RenderWindow &window);
		bool updateEvent(sf::Event &event, sf::RenderWindow &window, sf::Vector2f &windowSize) override;

		void setPosObj(sf::IntRect pos);
		void setPos(sf::IntRect pos);
		sf::Vector2i getToModal(void) const;

		sf::IntRect getPos() const override;
		void setColor(sf::Color color);

		bool getReached(void) const;
		IObjectSFML *getObj(void);

		protected:
		private:
		void moveObjectToEnd(void);

		IObjectSFML *_obj;
		sf::Vector2i _to;
		std::size_t _timeElapsed;
		bool _alreadyReached;

	};

}

#endif //PSU_ZAPPY_2017_MODAL_HPP
