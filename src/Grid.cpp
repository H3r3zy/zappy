//
// Created by wisenoa on 13/06/18.
//


#include <SFML/Graphics/Sprite.hpp>
#include "Grid.hpp"

Grid::Grid(const sf::Vector2f &mapSize) : _mapSize(mapSize), _nbActive(0)
{
	_font.loadFromFile("arial.ttf");
	loadTextures();
	loadMap();
}

Grid::~Grid()
{
	// TODO DELETE
}

void Grid::loadMap()
{
	std::mt19937 rng;
	rng.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 4);
	std::pair<sf::Vector2f, sf::Vector2f> dimension;

	dimension.second.x = 100;
	dimension.second.y = 100;
	srand(static_cast<unsigned int>(time(0)));
	for (uint j = 0; j < _mapSize.y; j++) {
		for (uint i = 0; i < _mapSize.x; i++) {
			dimension.first.x = i * 100;
			dimension.first.y = ((j) * 100);
			dimension.first.y *= -1;
			_gameMap.insert(GRID_MAP::value_type(POSITION(i, j), new Cell(dimension, _texturePack[dist6(rng)], _font)));
		}
	}
}

bool Grid::loadTextures()
{
	for (int i = 0; i < 6; i++) {
		_texturePack.emplace_back(new sf::Texture());
	}
	for (int i = 0; i < 5; i++) {
		if (!_texturePack[i]->loadFromFile("Grass" + std::to_string(i) + ".png")) {
			return false;
		}
	}

	for (int i = 0; i < 9; i++) {
		_textureCharacterPack[WALK_LEFT].emplace_back(sf::Texture());
		_textureCharacterPack[WALK_RIGHT].emplace_back(sf::Texture());
		_textureCharacterPack[WALK_UP].emplace_back(sf::Texture());
		_textureCharacterPack[WALK_DOWN].emplace_back(sf::Texture());
	}

	for (int i = 0; i < 9; i++) {
		_textureCharacterPack[WALK_UP][i].loadFromFile("Character.png", sf::IntRect(i * 64, 512, 64, 64));
		_textureCharacterPack[WALK_LEFT][i].loadFromFile("Character.png", sf::IntRect(i * 64, 576, 64, 64));
		_textureCharacterPack[WALK_DOWN][i].loadFromFile("Character.png", sf::IntRect(i * 64, 640, 64, 64));
		_textureCharacterPack[WALK_RIGHT][i].loadFromFile("Character.png", sf::IntRect(i * 64, 704, 64, 64));
	}
	return true;
}

void Grid::updateGrid3D(sf::View &view)
{
	_activeMap.clear();
	sf::Vector2f chunk;
	chunk.x = (view.getCenter().x) / 100 - 7 >= 0? (view.getCenter().x) / 100 - 7 : -1;
	chunk.y = ((view.getCenter().y * -1) / 100) - 10;
/*	std::cout << "Je suis en [" << view.getCenter().x << "][" << view.getCenter().y << "]" << std::endl;
	std::cout << "Mon chunk est en [" << chunk.x << "][" << chunk.y << "]" << std::endl;
	std::cout << "L calcul que je fais X:" << (view.getCenter().x) / 100 - 10 << std::endl;
	std::cout << "L calcul que je fais Y:" << (view.getCenter().y * - 1) / 100 - 10 << std::endl;*/
	// TODO dont push entities when left or e dessous
	sf::Vector2f to = chunk;
	to.x += 17;
	to.y += 17;
	while (chunk.y < to.y) {
		if (chunk.x >= 0 && chunk.y >= 0) {
			if (_gameMap.find(POSITION(static_cast<const uint &>(chunk.x), static_cast<const uint &>(chunk.y))) != _gameMap.end()) {
				_activeMap.push_back(_gameMap[POSITION(static_cast<const uint &>(chunk.x), static_cast<const uint &>(chunk.y))]);
			}
		}
		chunk.x++;
		if (chunk.x >= to.x) {
			chunk.x = (view.getCenter().x) / 100 - 7;
			chunk.y++;
			//std::cout << "mnt mon chunk vaut :" << chunk.y << " de haut et doit pas depasser " << to.y << std::endl;
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
		++_nbActive;
	}
	tmpRect.setFillColor(sf::Color::Cyan);
	window.draw(tmpRect);
}

uint Grid::getNbActive() const
{
	return _nbActive;
}

void Grid::displayMiniGrid(sf::RenderWindow &window, const sf::View &view, std::vector<Character> &character)
{
	sf::RectangleShape tmpRect;
	tmpRect.setSize(sf::Vector2f(10, 10));
	sf:: RectangleShape Grey;
	Grey.setPosition(view.getCenter() - view.getSize());
	Grey.setSize(sf::Vector2f(view.getSize().x * 2, view.getSize().y * 2));
	Grey.setFillColor(sf::Color(0, 0, 0, 127));

	window.draw(Grey);
	for (const auto &it : character) {
		tmpRect.setPosition(sf::Vector2f(it.getPosition()));
		window.draw(tmpRect);
	}
}

Cell *&Grid::getCell(int x, int y)
{
	return _gameMap[POSITION(x, y)];
}

bool Grid::checkvalid(int x, int y)
{
	std::cout << "je recoit" << x << " " << y << std::endl;
	if (x < 0 || y < 0)
		return false;
	return _gameMap.find(POSITION(static_cast<const uint &>(x), static_cast<const uint &>(y))) != _gameMap.end();
}

std::map<char, std::vector<sf::Texture>> &Grid::getTextureCharacter()
{
	return _textureCharacterPack;
}
