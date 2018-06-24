//
// Created by wisenoa on 17/06/18.
//


#ifndef PSU_ZAPPY_2017_AMOTIONSHAPE_HPP
#define PSU_ZAPPY_2017_AMOTIONSHAPE_HPP

#include <SFML/System.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <vector>
#include <map>
#include "IEntity.hpp"

class AMotionShape : public IEntity {
	public:
	AMotionShape();
	AMotionShape(sf::Vector2f &position);
	~AMotionShape() override;

	void setPosition(sf::Vector2f &position) override;
	void setPosition(float x, float y) override;
	uint getActualSprite() const;
	const sf::Vector2f &getPosition() const override;

	protected:
	std::map<char, std::vector<sf::Sprite>> _sprite;
	sf::Vector2f _position;
	uint _actualSprite = 0;

	private:
};

#endif //PSU_ZAPPY_2017_AMOTIONSHAPE_HPP
