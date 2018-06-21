//
// Created by wisenoa on 13/06/18.
//


#include <SFML/Graphics/Sprite.hpp>
#include <thread>
#include <Tools/Thread.hpp>
#include "Grid.hpp"

Grid::Grid(const sf::Vector2f &mapSize, sf::RenderWindow &window) : _mapSize(mapSize), _nbActive(0)
{
	std::cout << "nnike ta grosse chienne" << std::endl;
	std::cout << "je suis dans Grid, la taille de ma map map X" << _mapSize.x << " Y " << _mapSize.y << std::endl;

	window.setActive(false);
	auto thread(new my::Thread([&]() {loadingDisplay(_mapSize);}));
	loadTextures();
	loadMap();

	thread->join();
	window.setActive(true);
}

Grid::~Grid()
{
	// TODO DELETE
}


void Grid::loadingDisplay( sf::Vector2f &mapSize)
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Loading ");
	window.setPosition(sf::Vector2i(200, 100));
	sf::Text text;
	sf::Font font;
	std::string total = std::to_string(mapSize.x * mapSize.y);
	total.erase (total.find_last_not_of('0'), std::string::npos);
	float totalNb = (mapSize.x * mapSize.y);
	sf::Texture texture;
	sf::Sprite sprite;

	sf::RectangleShape totalRect;
	totalRect.setFillColor(sf::Color(0, 80, 0, 122));
	totalRect.setSize(sf::Vector2f(500, 50));
	totalRect.setPosition(100, 540);

	sf::RectangleShape currentRect;
	currentRect.setFillColor(sf::Color::Green);
	currentRect.setSize(sf::Vector2f(0, 50));
	currentRect.setPosition(100, 540);

	texture.loadFromFile("ronflex.png");
	sprite.setTexture(texture);

	font.loadFromFile("pokemon.ttf");
	text.setFont(font);
	text.setCharacterSize(20);
	text.setPosition(100, 0);

	while (!_ready) {
		text.setString("Creating cells : " + std::to_string(_blocNumber) + " / " + total);
		currentRect.setSize(sf::Vector2f((_blocNumber / totalNb) * 500, 50));
		window.draw(sprite);
		window.draw(totalRect);
		window.draw(currentRect);
		window.draw(text);
		window.display();
		window.clear();
	}
	window.close();
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
			dimension.first.y *= -1;
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
		if (!_texturePack[i]->loadFromFile("Grass" + std::to_string(i) + ".png")) {
			return false;
		}
	}

	for (int i = 0; i < 4; i++) {
		_waterPack.emplace_back(sf::Texture());
	}
	for (int i = 0; i < 4; i++) {
		if (!_waterPack[i].loadFromFile("Water" + std::to_string(i) + ".png")) {
			return false;
		}
	}

	for (int i = 0; i < 14; i++) {
		_resourcesPack.emplace_back(sf::Texture());
	}

	/* Food */
	_resourcesPack[0].loadFromFile("extra/gui/pokeball.png", sf::IntRect(0, 0, 60, 60));

	/* Pokeball */
	_resourcesPack[1].loadFromFile("extra/gui/pokeball.png", sf::IntRect(60, 0, 60, 60));
	_resourcesPack[2].loadFromFile("extra/gui/pokeball.png", sf::IntRect(120, 0, 60, 60));
	_resourcesPack[3].loadFromFile("extra/gui/pokeball.png", sf::IntRect(180, 0, 60, 60));
	_resourcesPack[4].loadFromFile("extra/gui/pokeball.png", sf::IntRect(240, 0, 60, 60));
	_resourcesPack[5].loadFromFile("extra/gui/pokeball.png", sf::IntRect(300, 0, 60, 60));
	_resourcesPack[6].loadFromFile("extra/gui/pokeball.png", sf::IntRect(360, 0, 60, 60));

	/* Multi Food */
	_resourcesPack[7].loadFromFile("extra/gui/pokeball2.png", sf::IntRect(0, 0, 50, 50));

	/* Multi Pokeball */
	_resourcesPack[8].loadFromFile("extra/gui/pokeball2.png", sf::IntRect(60, 0, 50, 50));
	_resourcesPack[9].loadFromFile("extra/gui/pokeball2.png", sf::IntRect(120, 0, 50, 50));
	_resourcesPack[10].loadFromFile("extra/gui/pokeball2.png", sf::IntRect(180, 0, 50, 50));
	_resourcesPack[11].loadFromFile("extra/gui/pokeball2.png", sf::IntRect(240, 0, 50, 50));
	_resourcesPack[12].loadFromFile("extra/gui/pokeball2.png", sf::IntRect(300, 0, 50, 50));
	_resourcesPack[13].loadFromFile("extra/gui/pokeball2.png", sf::IntRect(360, 0, 50, 50));


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
			} else {
			}
		} else {
			_mapBorder = true;
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

void Grid::loadWater()
{
	sf::Vector2f actualPos;
	sf::Vector2f destPos;

	destPos.x = 0;
	destPos.y = (_mapSize.y * -100);

	actualPos.x = -500;
	actualPos.y = 0;


	while (actualPos.y > destPos.y) {
		std::cout << "je creer un macaque en" << actualPos.x<< " "<< actualPos.y<< std::endl;
		_waterMap.emplace_back(actualPos, _waterPack);
		actualPos.x += 100;
		if (actualPos.x == destPos.x) {
			actualPos.x = -500;
			actualPos.y -= 100;
		}
	}
}
