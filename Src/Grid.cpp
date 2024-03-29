//
// EPITECH PROJECT, 2018
// Grid.cpp
// File description:
// Grid
//

#include <SFML/Graphics/Sprite.hpp>
#include <thread>
#include <Tools/Thread.hpp>
#include "Grid.hpp"

Grid::Grid(const sf::Vector2f &mapSize, sf::RenderWindow &window, std::vector<std::string> &teamName) : _mapSize(mapSize), _nbActive(0), _teamName(teamName)
{
	window.setActive(false);
	auto thread(new my::Thread([&]() {
		try {
			loadingDisplay(_mapSize, window);
		} catch (const std::exception &e){
		};
	}));
	loadTextures();
	loadMap();

	thread->join();
	window.setActive(true);
}

Grid::~Grid()
{
}


void Grid::loadingDisplay( sf::Vector2f &mapSize, sf::RenderWindow &window)
{
	window.setActive(true);
	sf::Text text;
	sf::Font font;
	std::string total = std::to_string(mapSize.x * mapSize.y);
	total.erase (total.find_last_not_of('0'), std::string::npos);
	float totalNb = (mapSize.x * mapSize.y);
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Texture texture_bck;
	sf::Sprite bck;

	sf::RectangleShape totalRect;
	totalRect.setFillColor(sf::Color(0, 80, 0, 122));
	totalRect.setSize(sf::Vector2f(500, 50));
	totalRect.setPosition(290, 490);

	sf::RectangleShape currentRect;
	currentRect.setFillColor(sf::Color::Green);
	currentRect.setSize(sf::Vector2f(0, 50));
	currentRect.setPosition(290, 490);

	if (!texture.loadFromFile("extra/game/ronflex.png"))
		throw std::exception();
	sprite.setTexture(texture);

	if (!texture_bck.loadFromFile("extra/game/loading_bck.png"))
		throw std::exception();
	bck.setTexture(texture_bck);
	bck.setScale(sf::Vector2f(1.5, 1.5));

	if (!font.loadFromFile("extra/pokemon.ttf"))
		throw std::exception();
	text.setFont(font);
	text.setCharacterSize(20);
	text.setPosition(100, 0);

	while (!_ready) {
		text.setString("Creating cells : " + std::to_string(_blocNumber) + " / " + total);
		currentRect.setSize(sf::Vector2f((_blocNumber / totalNb) * 500, 50));
		window.draw(bck);
		window.draw(sprite);
		window.draw(totalRect);
		window.draw(currentRect);
		window.draw(text);
		window.display();
		window.clear();
	}
}

void Grid::loadMap()
{
	std::mt19937 rng;
	rng.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 4);
	std::pair<sf::Vector2f, sf::Vector2f> dimension;

	dimension.second.x = 100;
	dimension.second.y = 100;
	for (uint j = 0; j < _mapSize.y; j++) {
		for (uint i = 0; i < _mapSize.x; i++) {
			dimension.first.x = i * 100;
			dimension.first.y = ((j) * 100);
			//dimension.first.y *= -1;
			++_blocNumber;
			_gameMap.insert(GRID_MAP::value_type(POSITION(i, j),
				new Cell(dimension, _texturePack[dist6(rng)], _resourcesPack)));
		}
	}
	loadWater();
	_ready = true;
}

bool Grid::loadTextures()
{
	for (int i = 0; i < 6; i++) {
		_texturePack.emplace_back(new sf::Texture());
	}
	for (int i = 0; i < 5; i++) {
		if (!_texturePack[i]->loadFromFile("extra/game/Grass" + std::to_string(i) + ".png"))
			throw std::exception();
	}

	for (int i = 0; i < 4; i++) {
		_waterPack.emplace_back(sf::Texture());
	}
	for (int i = 0; i < 4; i++) {
		if (!_waterPack[i].loadFromFile("extra/game/Water" + std::to_string(i) + ".png"))
			throw std::exception();
	}

	for (int i = 0; i < 14; i++) {
		_resourcesPack.emplace_back(sf::Texture());
	}

	/* Food */
	if (!_resourcesPack[0].loadFromFile("extra/gui/pokeball.png", sf::IntRect(0, 0, 60, 60)))
		throw std::exception();

	/* Pokeball */
	if (!_resourcesPack[1].loadFromFile("extra/gui/pokeball.png", sf::IntRect(60, 0, 60, 60)) || !_resourcesPack[2].loadFromFile("extra/gui/pokeball.png", sf::IntRect(120, 0, 60, 60)) ||
		!_resourcesPack[3].loadFromFile("extra/gui/pokeball.png", sf::IntRect(180, 0, 60, 60)) || !_resourcesPack[4].loadFromFile("extra/gui/pokeball.png", sf::IntRect(240, 0, 60, 60)) ||
		!_resourcesPack[5].loadFromFile("extra/gui/pokeball.png", sf::IntRect(300, 0, 60, 60)) || !_resourcesPack[6].loadFromFile("extra/gui/pokeball.png", sf::IntRect(360, 0, 60, 60)))
		throw std::exception();

	/* Multi Food */
	if (!_resourcesPack[7].loadFromFile("extra/gui/pokeball2.png", sf::IntRect(0, 0, 50, 50)))
		throw std::exception();

	/* Multi Pokeball */
	if (!_resourcesPack[8].loadFromFile("extra/gui/pokeball2.png", sf::IntRect(60, 0, 50, 50)) || !_resourcesPack[9].loadFromFile("extra/gui/pokeball2.png", sf::IntRect(120, 0, 50, 50)) ||
		!_resourcesPack[10].loadFromFile("extra/gui/pokeball2.png", sf::IntRect(180, 0, 50, 50)) || !_resourcesPack[11].loadFromFile("extra/gui/pokeball2.png", sf::IntRect(240, 0, 50, 50)) ||
		!_resourcesPack[12].loadFromFile("extra/gui/pokeball2.png", sf::IntRect(300, 0, 50, 50)) || !_resourcesPack[13].loadFromFile("extra/gui/pokeball2.png", sf::IntRect(360, 0, 50, 50)))
		throw std::exception();

	int textureFiles = 1;
	for (const auto &it : _teamName) {
		for (int i = 0; i < 9; i++) {
			_textureCharacterPack[it][WALK_LEFT].emplace_back(sf::Texture());
			_textureCharacterPack[it][WALK_RIGHT].emplace_back(sf::Texture());
			_textureCharacterPack[it][WALK_UP].emplace_back(sf::Texture());
			_textureCharacterPack[it][WALK_DOWN].emplace_back(sf::Texture());
			_textureCharacterPack[it][TAKE].emplace_back(sf::Texture());
			_textureCharacterPack[it][INCANT].emplace_back(sf::Texture());
			_textureCharacterPack[it][BROADCAST].emplace_back(sf::Texture());
			_textureCharacterPack[it][EGG].emplace_back(sf::Texture());
		}

		for (int i = 0; i < 9; i++) {
			if (!_textureCharacterPack[it][WALK_UP][i].loadFromFile("extra/game/Character" + std::to_string(textureFiles) + ".png", sf::IntRect(i * 64, 512, 64, 64)) ||
				!_textureCharacterPack[it][WALK_LEFT][i].loadFromFile("extra/game/Character" + std::to_string(textureFiles) + ".png", sf::IntRect(i * 64, 576, 64, 64)) ||
				!_textureCharacterPack[it][WALK_DOWN][i].loadFromFile("extra/game/Character" + std::to_string(textureFiles) + ".png", sf::IntRect(i * 64, 640, 64, 64)) ||
				!_textureCharacterPack[it][WALK_RIGHT][i].loadFromFile("extra/game/Character" + std::to_string(textureFiles) + ".png", sf::IntRect(i * 64, 704, 64, 64)) ||
				!_textureCharacterPack[it][TAKE][i].loadFromFile("extra/game/Character" + std::to_string(textureFiles) + ".png", sf::IntRect(i * 64, 1344, 64, 64)) ||
				!_textureCharacterPack[it][INCANT][i].loadFromFile("extra/game/Character" + std::to_string(textureFiles) + ".png", sf::IntRect(i * 64, 128, 64, 64)) ||
				!_textureCharacterPack[it][BROADCAST][i].loadFromFile("extra/game/Character" + std::to_string(textureFiles) + ".png", sf::IntRect(i * 64, 896, 64, 64)) ||
				!_textureCharacterPack[it][EGG][i].loadFromFile("extra/game/Character" + std::to_string(textureFiles) + ".png", sf::IntRect(i * 64, 768, 64, 64)))
				throw std::exception();
		}
		textureFiles++;
		if (textureFiles > 3)
			textureFiles = 1;
	}
	return true;
}

void Grid::updateGrid3D(sf::View &view)
{
	_activeMap.clear();
	sf::Vector2f chunk;
	chunk.x = (view.getCenter().x) / 100 - 7 >= 0? (view.getCenter().x) / 100 - 7 : -1;
	chunk.y = ((view.getCenter().y) / 100) - 10;
	sf::Vector2f to = chunk;
	to.x += 17;
	to.y += 17;
	while (chunk.y < to.y) {
		if (chunk.x >= 0 && chunk.y >= 0) {
			if (_gameMap.find(POSITION(static_cast<const uint &>(chunk.x), static_cast<const uint &>(chunk.y))) != _gameMap.end()) {
				_activeMap.push_back(_gameMap[POSITION(static_cast<const uint &>(chunk.x), static_cast<const uint &>(chunk.y))]);
			} else {
			}
		} else {
			_mapBorder = true;
		}
		chunk.x++;
		if (chunk.x >= to.x) {
			chunk.x = (view.getCenter().x) / 100 - 7;
			chunk.y++;
			////std::cout << "mnt mon chunk vaut :" << chunk.y << " de haut et doit pas depasser " << to.y << std::endl;
		}
	}

}

void Grid::displayGlobalGrid(sf::RenderWindow &window, const sf::View &view)
{
	_nbActive = 0;
	sf::RectangleShape tmpRect;
	tmpRect.setSize(sf::Vector2f(10, 10));
	tmpRect.setPosition(view.getCenter());
	for (const auto &it : _activeMap) {
		window.draw(it->getCell());
		window.draw(it->getCellPos());
		it->printAllResources(window);

		++_nbActive;
	}
	for (auto &it : _waterMap) {
		window.draw(it.getSprite());
	}
	tmpRect.setFillColor(sf::Color::Cyan);
	window.draw(tmpRect);
}

uint Grid::getNbActive() const
{
	return _nbActive;
}

void Grid::displayMiniGrid(sf::RenderWindow &window, const sf::View &view, std::map<uint, Character> &character, std::map<std::string, sf::Color> &colorTeam)
{
	sf::RectangleShape tmpRect;
	tmpRect.setSize(sf::Vector2f(10, 10));
	sf:: RectangleShape Grey;
	Grey.setPosition(view.getCenter() - view.getSize());
	Grey.setSize(sf::Vector2f(view.getSize().x * 2, view.getSize().y * 2));
	Grey.setFillColor(sf::Color(0, 0, 0, 127));

	window.draw(Grey);
	for (const auto &it : character) {
		tmpRect.setPosition(sf::Vector2f(it.second.getPosition()));
		tmpRect.setFillColor(colorTeam[it.second.getPlayerTeam()]);
		window.draw(tmpRect);
	}
}

Cell *&Grid::getCell(int x, int y)
{
	return _gameMap[POSITION(x, y)];
}

bool Grid::checkvalid(int x, int y)
{
	if (x < 0 || y < 0)
		return false;
	return _gameMap.find(POSITION(static_cast<const uint &>(x), static_cast<const uint &>(y))) != _gameMap.end();
}

std::map<std::string, std::map<char, std::vector<sf::Texture>>> &Grid::getTextureCharacter()
{
	return _textureCharacterPack;
}

void Grid::loadWater()
{
	return;
	sf::Vector2f actualPos;
	sf::Vector2f destPos;

	destPos.x = 0;
	destPos.y = (_mapSize.y * -100);

	actualPos.x = -500;
	actualPos.y = 0;


	while (actualPos.y > destPos.y) {
		//std::cout << "je creer un macaque en" << actualPos.x<< " "<< actualPos.y<< std::endl;
		_waterMap.emplace_back(actualPos, _waterPack);
		actualPos.x += 100;
		if (actualPos.x == destPos.x) {
			actualPos.x = -500;
			actualPos.y -= 100;
		}
	}
}
