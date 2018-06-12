/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Created by martin.januario@epitech.eu,
*/

#ifndef CPP_PLAZZA_IOBJECTSFML_HPP
# define CPP_PLAZZA_IOBJECTSFML_HPP

# include <SFML/Graphics.hpp>
# include <vector>
# include <string>
# include <memory>
#include <functional>

namespace irc {

	enum MouseEvent {
		CLICK,
		CLICKOUT,
		HOVER,
		HOVEROUT,
		SCROLLDOWN,
		SCROLLUP,
	};

	class IObjectSFML {
		public:
		IObjectSFML() = default;
		virtual ~IObjectSFML() = default;

		virtual void setBoolUsed(bool used) = 0;
		virtual bool getBoolUsed(void) const = 0;

		virtual void setBoolDisplay(bool display) = 0;
		virtual bool getBoolDisplay() const = 0;

		virtual void setScrollUsed(bool opt) = 0;
		virtual void setScrollLimitTop(int max) = 0;
		virtual void setScrollLimitDown(int max) = 0;

		virtual void setLayer(std::size_t layer) = 0;
		virtual std::size_t getLayer(void) const = 0;

		virtual void setPos(sf::IntRect pos) = 0;
		virtual sf::IntRect getPos(void) const = 0;

		virtual void setColor(sf::Color) = 0;

		virtual bool updateEvent(sf::Event &event, sf::RenderWindow &window, sf::Vector2f &windowSize) = 0;
		virtual bool drawObject(sf::RenderWindow &window) = 0;

		template<class Callable, class... Args>
		void addFuncMouseEvent(irc::MouseEvent type, Callable &&func, Args &&... args) {
			auto f = std::bind(
				std::forward<Callable>(func),
				std::forward<Args>(args)...);

			_funcMouseEvent[type] = [f] {
				f();
			};
		};

		template<class Callable, class... Args>
		void addFuncKeyEvent(sf::Keyboard::Key type, Callable &&func, Args &&... args) {
			auto f = std::bind(
				std::forward<Callable>(func),
				std::forward<Args>(args)...);

			_keyBinding.insert({type, [f] {
				f();
			}});
		};

		protected:
		std::map<sf::Keyboard::Key, std::function<void(void)>> _keyBinding;
		std::map<irc::MouseEvent, std::function<void(void)>> _funcMouseEvent;
		sf::Vector2i _limitScroll; // x = top, y = bot
	};
}

#endif //CPP_PLAZZA_IOBJECTSFML_HPP
