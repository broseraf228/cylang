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
	
	sf::RenderWindow window(sf::VideoMode(1200, 800), "SFML game");

	GameMap gameMap(&window, 1,1);

	resManager.loadTexture("fne", "img\\floor_not_effect.png");
	sf::Texture textur;
	textur = resManager.getTexture("fne");
	sf::Sprite sprite;
	sprite.setTexture(textur);
	sprite.setTextureRect(sf::IntRect(0,0,32,32));
	sprite.setPosition(100,100);

	gameMap.loadMapFromStr(resManager.loadMap("map1"));
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
		gameMap.draw();
		window.draw(sprite);
		window.display();



		sf::Time elapsed = clock.restart();
		float fps = 1.0f / elapsed.asSeconds();
		window.setTitle(std::to_string(fps));
	}

	return 0;
}