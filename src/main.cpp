#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <string>
#include "GameMap.hpp"

std::map<int, sf::Color> colorMap;

int main() {
	colorMap[0] = sf::Color::Black;
	colorMap[1] = sf::Color::White;
	colorMap[2] = sf::Color::Red;
	colorMap[3] = sf::Color::Green;
	colorMap[4] = sf::Color::Blue;
	
	sf::RenderWindow window(sf::VideoMode(1600, 1200), "SFML game");
	//window.setVerticalSyncEnabled(true);

	GameMap gameMap(&window, 48,48);

	gameMap.setMapSize();
	gameMap.fillMap();
	gameMap.fillVertexArray();


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
		window.draw(*(gameMap.getVertexArray()));
		window.display();

		//gameMap.fillMap();
		//gameMap.fillVertexArray();

		
		// Calculate and print FPS
		sf::Time elapsed = clock.restart();
		float fps = 1.0f / elapsed.asSeconds();
		window.setTitle(std::to_string(fps));
	}

	return 0;
}