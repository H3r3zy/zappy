/*
** EPITECH PROJECT, 2018
** PSU_myirc_2017
** File description:
** Created by martin.januario@epitech.eu,
*/

#ifndef PSU_MYIRC_2017_CONTAINER_HPP
# define PSU_MYIRC_2017_CONTAINER_HPP

# include <string>
# include <map>
# include "AbsractObjectSFML.hpp"

namespace irc {
	class Container : public AbstractObjectSFML {
		public:
		Container(sf::IntRect pos);
		~Container();

		void addObjectList(std::string name, IObjectSFML *obj, int layer = 0);
		bool updateEvent(sf::Event &event, sf::RenderWindow &window, sf::Vector2f &windowSize) override;
		void setLayer(std::size_t layer) override;
		bool drawObject(sf::RenderWindow &window);
		IObjectSFML *getObjectByName(std::string name);

		void breakEvent();
		void setPos(sf::IntRect pos);
		void setColor(sf::Color color);

		private:
		std::map<std::string, irc::IObjectSFML *> _listObject;
		bool _break;
	};
}

#endif //PSU_MYIRC_2017_CONTAINER_HPP
