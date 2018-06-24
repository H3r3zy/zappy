//
// Created by wisenoa on 17/06/18.
//


#ifndef PSU_ZAPPY_2017_ATEXT_HPP
#define PSU_ZAPPY_2017_ATEXT_HPP

#include <SFML/Graphics/Text.hpp>

class AText {
	public:
	explicit AText(const sf::Font &font, sf::Vector2f &position, uint characterSize = 16);

	AText();

	virtual ~AText();

	void setText(const std::string &text);
	const sf::Text &getText() const;
	void setPosition(const sf::Vector2f &position);
	void setPosition(float x, float y);
	const sf::Vector2f &getPosition() const;

	protected:
	sf::Text _text;
	sf::Vector2f _position;

	private:
};

#endif //PSU_ZAPPY_2017_ATEXT_HPP
