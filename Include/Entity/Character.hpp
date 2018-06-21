//
// Created by wisenoa on 15/06/18.
//


#ifndef PSU_ZAPPY_2017_CHARACTER_HPP
#define PSU_ZAPPY_2017_CHARACTER_HPP

#include <iostream>
#include <map>
#include <chrono>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <Entity/AMotionShape.hpp>

class Character : public AMotionShape {
	typedef std::chrono::time_point<std::chrono::system_clock> chrono_t;
	enum {
		WALK_UP = 1,
		WALK_RIGHT = 2,
		WALK_DOWN = 3,
		WALK_LEFT = 4
	};
	public:
	Character(std::map<char, std::vector<sf::Texture>> &_texturePack, sf::Vector2f &position, uint id);

	void setPlayerTeam(const std::string &teamName);
	const std::string &getPlayerTeam() const;

	void setPlayerOrientation(char orientation);
	const char getPlayerOrientation() const;

	const uint &getPlayerID() const;

	void setPlayerLevel(uint level);
	const uint &getPlayerLevel() const;

	static bool playerLoop(sf::RenderWindow &window);

	sf::Sprite &getCharacter();

	~Character();

	private:
	chrono_t _beginTime;
	std::string _teamName;
	char _action;
	char _orientation;
	uint _id;
	uint _level;


	// TODO LE DEGAGER
	int _testTmp = 0;
	int _randomDirection = 2;
	bool oneTime = true;


};

#endif //PSU_ZAPPY_2017_CHARACTER_HPP
