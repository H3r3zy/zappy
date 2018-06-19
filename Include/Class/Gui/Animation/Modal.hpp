/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Created by martin.januario@epitech.eu,
*/

#ifndef CPP_PLAZZA_MODAL_HPP
# define CPP_PLAZZA_MODAL_HPP

# include "AbsractObjectSFML.hpp"

namespace irc {
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

#endif //CPP_PLAZZA_MODAL_HPP
