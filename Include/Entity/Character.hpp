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
		WALK_LEFT = 4,
		TAKE = 5,
		INCANT = 6,
		BROADCAST = 7
	};
	public:
	Character(std::map<char, std::vector<sf::Texture>> &_texturePack, sf::Vector2f &position, uint id, int freq, const sf::Vector2f &mapSize);

	void setPlayerTeam(const std::string &teamName);
	const std::string &getPlayerTeam() const;

	void setPlayerOrientation(char orientation, int duration);
	char getPlayerOrientation() const;

	const uint &getPlayerID() const;

	void setPlayerLevel(uint level);
	const uint &getPlayerLevel() const;

	void setPlayerMovement(sf::Vector2f &finalPos, const uint &orientation, int freq, int duration);
	void setPlayerTake(int freq, int duration);
	void setPlayerIncant(int freq, int duration, sf::Vector2f &newPos);
	void setPlayerBroadcast(int freq, int duration);
	void levelUp();

	const sf::Vector2f &getPlayerPosition() const;

	sf::Sprite &getCharacter();
	bool getAction() const;

	~Character();

	private:
	void checkOutMap();
	sf::Vector2f _mapSize;
	chrono_t _beginTime;
	std::string _teamName;
	sf::Vector2f _nextPos;
	bool _action = false;
	char _orientation = 1;
	uint _id;
	uint _level;
	int _freq = 1;
	double _totalDist = 0;
	int _duration = 7;
	int _nextFrameTime = 0;

	bool oneTime = false;
};

#endif //PSU_ZAPPY_2017_CHARACTER_HPP
