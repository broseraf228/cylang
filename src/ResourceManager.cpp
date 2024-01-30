#include "ResourceManager.hpp"

ResourceManager::ResourceManager(std::string i_path)
{
	//обрезаю путо до екзешника к пути до папки
	int i = i_path.length();
	while (i_path[i] != '/' && i_path[i] != '\\') {
		i_path.erase(i);
		i--;
	}
	//добавл€ю путо до папки ресурсов
	i_path.append("res\\");
	m_path = i_path;
	std::cout << "the data path: " << m_path << std::endl;
}

std::string ResourceManager::loadStringFromFile(std::string i_path)
{
	std::ifstream f(m_path + i_path);
	std::stringstream ss;
	ss << f.rdbuf();
	if (ss.str().empty()) {
		std::cout << "can't load the file: " << i_path << std::endl;
		return "";
	}
	return ss.str();
}

std::string ResourceManager::loadMap(std::string mapName)
{
	std::string loaded = loadStringFromFile("maps\\" + mapName + ".txt");
	if (loaded.empty()) {
		std::cout << "can't load the map: " << mapName << std::endl;
		return "0";
	}
	return loaded;
}

sf::Texture& ResourceManager::loadTexture(std::string texName, std::string i_path)
{
	sf::Texture tmp_texture;
	if (!tmp_texture.loadFromFile(m_path + i_path)) {
		std::cout << "can't load image: " << i_path << std::endl;
		return sf::Texture();
	}
	std::cout << "load image: " << i_path << std::endl;
	m_textureMap[texName] = tmp_texture;
	return m_textureMap[texName];
}

sf::Texture& ResourceManager::getTexture(std::string texName)
{
	sf::Texture tmp_texture;
	return m_textureMap[texName];
}