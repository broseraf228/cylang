#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include "GameMap.hpp"
#include "ResourceManager.hpp"


int main(int argc, char* argv[]) {
	std::string i_path;
	i_path = argv[0];
	ResourceManager resManager(i_path);
	std::cout << resManager.loadStringFromFile("maps\\map1.txt") << std::endl;
	
	sf::RenderWindow window(sf::VideoMode(1200, 800), "SFML game", sf::Style::Fullscreen);
	window.setVerticalSyncEnabled(true);

	GameMap gameMap(&window, &resManager, 1,1);


	gameMap.loadMapFromStr(resManager.loadMap("map1"));


	sf::Clock clock;
	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed)
				if (event.key.code == sf::Keyboard::Escape)
					window.close();
		}

		window.clear();
		gameMap.draw();
		window.display();



		sf::Time elapsed = clock.restart();
		float fps = 1.0f / elapsed.asSeconds();
		window.setTitle(std::to_string(fps));
	}

	return 0;
}