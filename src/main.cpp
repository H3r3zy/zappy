//
// EPITECH PROJECT, 2018
// main.cpp
// File description:
// main
//

#ifdef _DEBUG
#pragma comment(lib,"sfml-graphics-d.lib")
#pragma comment(lib,"sfml-audio-d.lib")
#pragma comment(lib,"sfml-system-d.lib")
#pragma comment(lib,"sfml-window-d.lib")
#pragma comment(lib,"sfml-network-d.lib")
#else
#pragma comment(lib,"sfml-graphics.lib")
#pragma comment(lib,"sfml-audio.lib")
#pragma comment(lib,"sfml-system.lib")
#pragma comment(lib,"sfml-window.lib")
#pragma comment(lib,"sfml-network.lib")
#endif
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <GL/glu.h>
#ifndef GL_SRGB8_ALPHA8
#define GL_SRGB8_ALPHA8 0x8C43
#endif
#include <SFML/Window.hpp>
#include <iostream>
#include "Map.hpp"

int main(int ac, char **av)
{


	Map map(std::stoi(av[1]));

	map.gameLoop();
	printf("cocou");
/*	sf::Texture texture;
	texture.loadFromFile("map.jpg");
	sf::Sprite sprite;
	sprite.setTexture(texture);



	sf::View view1(sf::FloatRect(200, 200, 300, 200));
	sf::View minimapView;
	// Declare and create a new render-window
	minimapView.setViewport(sf::FloatRect(0.75f, 0, 0.25f, 0.25f));

	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
	// Limit the framerate to 60 frames per second (this step is optional)
	sf::Clock clock;
	int fps = 0;
	//window.setFramerateLimit(60);
	// The main loop - ends as soon as the window is closed
	while (window.isOpen()) {
		// Event processing
		sf::Event event;
		while (window.pollEvent(event)) {
			// Request for closing the window
			if (event.type == sf::Event::Closed)
				window.close();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				std::cout << "jai appuye a droite" << std::endl;
				view1.move(2, 0);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				std::cout << "jai appuye a droite" << std::endl;
				view1.move(-2, 0);
			}
			if (event.type == sf::Event::Resized)
			{
				// update the view to the new size of the window
				sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
				window.setView(sf::View(visibleArea));
			}
		}
		window.setView(view1);

		sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
		std::cout << pixelPos.x << "  " << pixelPos.y << std::endl;

		sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos, view1);
		std::cout << worldPos.x << "  " <<  worldPos.y << std::endl;




		for (const auto &it : map) {
			window.draw(it);
		}
		window.draw(sprite);
		window.setView(minimapView);
		for (const auto &it : map) {
			window.draw(it);
		}

		window.draw(sprite);
		window.display();
		// Clear the whole window before rendering a new frame
		window.clear();
	}*/
}