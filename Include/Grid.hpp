//
// Created by wisenoa on 13/06/18.
//


#ifndef PSU_ZAPPY_2017_GRID_HPP
#define PSU_ZAPPY_2017_GRID_HPP

#include <SFML/System.hpp>
#include <map>
#include <random>
#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <Entity/Water.hpp>
#include "Entity/Cell.hpp"
#include "Character.hpp"

class Grid {

	enum {
		GRASS,
		GRASS1,
		GRASS2,
		GRASS3,
		GRASS4
	};

	enum {
		WALK_UP = 1,
		WALK_RIGHT = 2,
		WALK_DOWN = 3,
		WALK_LEFT = 4,
		TAKE = 5
	};

	typedef std::pair<uint, uint> 				POSITION;
	typedef std::map<std::pair<uint, uint>, Cell *>  	GRID_MAP;

	public:
	Grid(const sf::Vector2f &mapSize, sf::RenderWindow &window, std::vector<std::string> &teamName);
	void displayGlobalGrid(sf::RenderWindow &window, const sf::View &view);
	void displayMiniGrid(sf::RenderWindow &window, const sf::View &view, std::map<uint, Character> &character);
	void updateGrid3D(sf::View &view);
	uint getNbActive() const;
	bool checkvalid(int x, int y);
	std::map<std::string, std::map<char, std::vector<sf::Texture>>> &getTextureCharacter();
	Cell *&getCell(int x, int y);
	~Grid();

	private:
	bool loadTextures();
	void loadMap();
	void loadWater();
	void loadingDisplay( sf::Vector2f &mapSize, sf::RenderWindow &window);

	/* TOOLS */
	sf::Vector2f _mapSize;
	uint _nbActive;
	std::vector<Water> _waterMap;
	std::vector<Cell *> _activeMap;
	std::map<std::pair<uint, uint>, Cell *> _gameMap;
	std::vector<std::string> &_teamName;


	bool _mapBorder = false;
	bool _ready = false;
	int _blocNumber = 0;

	/*  SFML */
	std::map<std::string, std::map<char, std::vector<sf::Texture>>> _textureCharacterPack;
	std::vector<sf::Texture *> _texturePack;
	std::vector<sf::Texture> _waterPack;
	std::vector<sf::Texture> _resourcesPack;
};

#endif //PSU_ZAPPY_2017_GRID_HPP