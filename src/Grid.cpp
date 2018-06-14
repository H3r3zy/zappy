//
// Created by wisenoa on 13/06/18.
//


#include "Grid.hpp"

Grid::Grid(const sf::Vector2f &mapSize) : _mapSize(mapSize)
{
	std::pair<sf::Vector2f, sf::Vector2f> dimension;
	dimension.second.x = 100;
	dimension.second.y = 100;
	for (uint j = 0; j < _mapSize.y; j++) {
		for (uint i = 0; i < _mapSize.x; i++) {
			dimension.first.x = i * 100;
			dimension.first.y = j * 100;
			_gameMap.insert(GRID_MAP::value_type(POSITION(i, j), new Cell(dimension)));
		}
	}
	_font.loadFromFile("arial.ttf");
	_text.setFont(_font);
	_text.setFillColor(sf::Color::Red);
	_text.setCharacterSize(16);
}

Grid::~Grid()
{
	// TODO delete map
}

void Grid::updateGrid3D(sf::View &view)
{
	_activeMap.clear();
	sf::Vector2f chunk;
	chunk.x = (view.getCenter().x) / 100 - 7 >= 0? (view.getCenter().x) / 100 - 7 : 0;
	chunk.y = ((view.getCenter().y * -1) / 100) - 10 > 0 ? (view.getCenter().y * -1) / 100 - 10 : 0;
/*	std::cout << "Je suis en [" << view.getCenter().x << "][" << view.getCenter().y << "]" << std::endl;
	std::cout << "Mon chunk est en [" << chunk.x << "][" << chunk.y << "]" << std::endl;
	std::cout << "L calcul que je fais X:" << (view.getCenter().x) / 100 - 10 << std::endl;
	std::cout << "L calcul que je fais Y:" << (view.getCenter().y * - 1) / 100 - 10 << std::endl;*/
	sf::Vector2f to = chunk;
	to.x += 17;
	to.y += 17;
	std::cout << chunk.y << std::endl;
	while (chunk.y < to.y) {
		if (chunk.x >= 0 && chunk.y >= 0) {
			if (_gameMap.find(POSITION(static_cast<const uint &>(chunk.x), static_cast<const uint &>(chunk.y))) != _gameMap.end()) {
				_activeMap.push_back(_gameMap[POSITION(static_cast<const uint &>(chunk.x), static_cast<const uint &>(chunk.y))]);
			}
		}
		chunk.x++;
		if (chunk.x >= to.x) {
			chunk.x = (view.getCenter().x) / 100 - 7 >= 0? (view.getCenter().x) / 100 - 7 : 0;
			chunk.y++;
			//std::cout << "mnt mon chunk vaut :" << chunk.y << " de haut et doit pas depasser " << to.y << std::endl;
		}
	}

}

void Grid::displayGlobalGrid(sf::RenderWindow &window, const sf::View &view)
{
	int i = 0;
	float tmpX = 0;
	float tmpY = 0;

	float tmpXX = 0;
	float tmpYY = 0;


	for (const auto &it : _activeMap) {
		window.draw(it->drawCell());
		_text.setPosition(it->getPos());
		_text.setString(it->getStringPos());
		window.draw(_text);
		i++;
	}
	std::cout << "X " << tmpXX << " " << tmpX << " Y " << tmpYY << " " << tmpY << std::endl;
	std::cout << "jai affiché :" << i << "elements" << std::endl;
}

sf::Text &Grid::getcaca()
{
	return _text;
}
