/*
** EPITECH PROJECT, 2018
** PSU_ZAPPY_2017
** File description:
** Created by martin.januario@epitech.eu,
*/

#ifndef PSU_ZAPPY_2017_TEXTINPUT_HPP
# define PSU_ZAPPY_2017_TEXTINPUT_HPP

# include <string>
# include "AbsractObjectSFML.hpp"

namespace zap {
	class TextInput : public AbstractObjectSFML {
		public:
		TextInput(const std::string &pathFont, sf::IntRect pos);
		~TextInput() = default;

		bool updateEvent(sf::Event &event, sf::RenderWindow &window, sf::Vector2f &windowSize) override;

		bool drawObject(sf::RenderWindow &window) override;
		void setPos(sf::IntRect pos) override;
		void setColor(sf::Color color) override;

		void setBlockPrompt(bool block);
		bool getBlockPrompt(void) const;

		void clearPrompt(void);
		void setPrompt(std::string newPrompt);
		std::string getPrompt(void) const;

		void initStringThenDraw(std::string &);

		private:
		void updateString(sf::Event event);
		void leftKey(void);
		void rightKey(void);
		void deleteKey(void);
		void backspaceKey(void);
		void textKey(sf::Event event);

		sf::Font _font;
		sf::Text _text;

		std::string _prompt;
		int _index;
		bool _block = true;
	};
}

#endif //PSU_ZAPPY_2017_TEXTINPUT_HPP
