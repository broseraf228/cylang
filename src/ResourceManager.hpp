#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

class ResourceManager {
private:
	std::string m_path;
	//std::map<std::string, std::shared_ptr<sf::Texture>> m_textureMap;    возможно пригодится
	std::map<std::string, sf::Texture > m_textureMap;
public:
	ResourceManager(std::string i_path);

	std::string loadStringFromFile(std::string i_path);

	std::string loadMap(std::string i_path);

	sf::Texture& loadTexture(std::string texName, std::string i_path);
	//sf::Texture& getTexture(std::string texName);
	sf::Texture& getTexture(std::string texName);

};