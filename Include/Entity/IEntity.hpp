//
// EPITECH PROJECT, 2018
// IEntity.hpp
// File description:
// IEntity.hpp
//

#ifndef PSU_ZAPPY_2017_IENTITY_HPP
#define PSU_ZAPPY_2017_IENTITY_HPP

#include <SFML/System.hpp>

class IEntity {
	public:
	IEntity() = default;
	virtual ~IEntity() = default;
	virtual void setPosition(sf::Vector2f &position) = 0;
	virtual void setPosition(float x, float y) = 0;
	virtual const sf::Vector2f &getPosition() const = 0;

	protected:

	private:
};

#endif //PSU_ZAPPY_2017_IENTITY_HPP
