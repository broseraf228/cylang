#include "GameMap.hpp"
#include "m_std.hpp"
#include <iostream>


Tile::Tile(std::string texName, ResourceManager& resMan) {
	texture = texName;
}
Tile::Tile() {

}


GameMap::GameMap(sf::RenderWindow* window, ResourceManager* i_resourceManager, int mapSX, int mapSY) {
	//сохран€ю переменные
	m_window = window;
	m_resourceManager = i_resourceManager;
	m_windowSizeX = (*window).getSize().x;
	m_windowSizeY = (*window).getSize().y;
	m_mapSizeX = mapSX;
	m_mapSizeY = mapSY;
}
GameMap::~GameMap() {}

void GameMap::loadMapFromStr(std::string inMap) {
	std::vector<std::string> splittedMapf = splitString(inMap, '\n');
	//загрузка таблицы тайлов
	std::string current_str;
	std::vector <std::string> current_str_list;
	while (splittedMapf[0][0] == '@') 
	{
		current_str = splittedMapf[0];
		current_str.erase(current_str.begin());
		current_str_list = splitString(current_str, ',');
		(*m_resourceManager).loadTexture(current_str_list[0], current_str_list[1]);
		splittedMapf.erase(splittedMapf.cbegin());
	}

	//этап загрузки карты
	std::vector<std::vector<std::string>> splittedMap;
	splittedMap.resize(splittedMapf.size());
	for (int i = 0; i < splittedMapf.size(); i++) {
		splittedMap[i] = splitString(splittedMapf[i], ' ');
	}

	m_mapSizeX = splittedMap[0].size();
	m_mapSizeY = splittedMap.size();
	setMapSize();
	for (int ix = 0; ix < m_mapSizeX; ix++) {
		for (int iy = 0; iy < m_mapSizeY; iy++) {
			m_map[ix][iy] = Tile(splittedMap[iy][ix], *m_resourceManager);
		}
	}

	//все дл€ корректного отображени€ карты
	//масштабирую карту под размеры окна (Ќ≈ “–ќ√ј“№ ѕќ ј Ќ≈ —Ћќћј≈“—я)
	double rat = (double)m_mapSizeX / m_mapSizeY;

	m_mapOnScreenSizeX = (double)(m_windowSizeY * m_mapSizeX) / m_mapSizeY;
	m_mapOnScreenSizeY = (double)m_windowSizeY;

	if (m_mapOnScreenSizeX > m_windowSizeX || m_mapOnScreenSizeY > m_windowSizeY) {
		m_mapOnScreenSizeX = (double)m_windowSizeX;
		m_mapOnScreenSizeY = (double)(m_windowSizeX * m_mapSizeY) / m_mapSizeX;
	}
	//вычисл€ю размер тайла в пиксел€х
	tileSize = (float)m_mapOnScreenSizeX / m_mapSizeX;
	generateRenderTextur();
}


void GameMap::setMapSize(int sX, int sY) {
	m_mapSizeX = sX;
	m_mapSizeY = sY;
	setMapSize();
}
void GameMap::setMapSize() {
	m_map.resize(m_mapSizeX);
	for (int i = 0; i < m_map.size(); i++)
		m_map[i].resize(m_mapSizeY);
}


void GameMap::generateRenderTextur()
{
	float scale = tileSize / 32;

	m_renderTexture.create(m_mapOnScreenSizeX, m_mapOnScreenSizeY);
	sf::Sprite tmp_sprite;

	for (int ix = 0; ix < m_mapSizeX; ix++) {
		for (int iy = 0; iy < m_mapSizeY; iy++) {
			tmp_sprite.setTexture((*m_resourceManager).getTexture(m_map[ix][iy].texture));
			tmp_sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
			tmp_sprite.setPosition(sf::Vector2f(ix * tileSize, iy * tileSize));
			tmp_sprite.setScale(scale, scale);
			m_renderTexture.draw(tmp_sprite);
		}
	}
	int offsetX = (m_windowSizeX - m_mapOnScreenSizeX) * 0.5;
	int offsetY = (m_windowSizeY - m_mapOnScreenSizeY) * 0.5;
	m_renderSprite.setTexture(m_renderTexture.getTexture());
	m_renderSprite.setTextureRect(sf::IntRect(0, 0, m_mapOnScreenSizeX, m_mapOnScreenSizeY));
	m_renderSprite.setPosition(sf::Vector2f(offsetX, offsetY));

}


void GameMap::draw() {
	(*m_window).draw(m_renderSprite);
}
void GameMap::draw(bool old) {
	sf::Sprite tmp_sprite;
	int offsetX = (m_windowSizeX - m_mapOnScreenSizeX) * 0.5;
	int offsetY = (m_windowSizeY - m_mapOnScreenSizeY) * 0.5;
	float scale = tileSize / 32;

	for (int ix = 0; ix < m_mapSizeX; ix++) {
		for (int iy = 0; iy < m_mapSizeY; iy++) {
			tmp_sprite.setTexture((*m_resourceManager).getTexture(m_map[ix][iy].texture));
			tmp_sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
			tmp_sprite.setPosition(sf::Vector2f(ix * tileSize + offsetX, iy * tileSize + offsetY));
			tmp_sprite.setScale(scale, scale);
			(*m_window).draw(tmp_sprite);
		}
	}
}














sf::VertexArray& GameMap::getVertexArray() {
	return m_vertexArray;
}
void GameMap::addSqare(int posX, int posY, sf::Color color) {
	m_vertexArray.append(sf::Vertex(sf::Vector2f(posX, posY), color));
	m_vertexArray.append(sf::Vertex(sf::Vector2f(posX + tileSize, posY), color));
	m_vertexArray.append(sf::Vertex(sf::Vector2f(posX + tileSize, posY + tileSize), color));
	m_vertexArray.append(sf::Vertex(sf::Vector2f(posX, posY + tileSize), color));
}
void GameMap::addSqare(int posX, int posY, int sizeX, int sizeY, sf::Color color) {
	m_vertexArray.append(sf::Vertex(sf::Vector2f(posX, posY), color));
	m_vertexArray.append(sf::Vertex(sf::Vector2f(posX + sizeX, posY), color));
	m_vertexArray.append(sf::Vertex(sf::Vector2f(posX + sizeX, posY + sizeY), color));
	m_vertexArray.append(sf::Vertex(sf::Vector2f(posX, posY + sizeY), color));
}
