/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Created by martin.januario@epitech.eu,
*/

#ifndef CPP_PLAZZA_ABSRACTOBJECTSFML_HPP
# define CPP_PLAZZA_ABSRACTOBJECTSFML_HPP

# include <map>
# include <vector>
# include "IObjectSFML.hpp"

namespace irc {

	class AbstractObjectSFML : public IObjectSFML {
		public:
		AbstractObjectSFML(sf::IntRect pos);
		virtual ~AbstractObjectSFML() override = default;

		void setBoolUsed(bool used) override;
		bool getBoolUsed(void) const override;

		void setBoolDisplay(bool display);
		bool getBoolDisplay() const;

		void setScrollUsed(bool opt) override;
		void setScrollLimitTop(int max) override;
		void setScrollLimitDown(int max) override;

		sf::IntRect getPos(void) const;

		void setLayer(std::size_t layer) override;
		std::size_t getLayer(void) const override;

		bool updateEvent(sf::Event &event, sf::RenderWindow &window, sf::Vector2f &windowSize) override;

		protected:
		void managePosMouse(sf::Event &event, sf::RenderWindow &window, sf::Vector2f &windowSize);
		void manageKeyBinding(sf::Event &event);
		void manageScroll(sf::Event &event);

		sf::IntRect _pos;
		sf::Color _color;


		bool _isUsed;
		bool _scrollUsed;
		std::size_t _layer;
		bool _display = true;

		private:
	};
}

#endif //CPP_PLAZZA_ABSRACTOBJECTSFML_HPP
