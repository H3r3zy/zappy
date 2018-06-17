//
// Created by wisenoa on 17/06/18.
//


#ifndef PSU_ZAPPY_2017_ARECTANGLESHAPE_HPP
#define PSU_ZAPPY_2017_ARECTANGLESHAPE_HPP

#include <SFML/Graphics/RectangleShape.hpp>
#include "IEntity.hpp"

class ARectangleShape : public IEntity {
	public:
	ARectangleShape(sf::Vector2f &position, sf::Vector2f &size);
	~ARectangleShape() override;
	void setPosition(sf::Vector2f &position) override;
	void setPosition(float x, float y) override;
	const sf::Vector2f &getPosition() const override;

	sf::RectangleShape &getCell();

	protected:
	sf::RectangleShape _rectangle;
	sf::Vector2f _position;
	sf::Vector2f _size;

	private:
};

#endif //PSU_ZAPPY_2017_ARECTANGLESHAPE_HPP
