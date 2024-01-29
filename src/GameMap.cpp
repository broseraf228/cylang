#include "GameMap.hpp"
#include <iostream>


GameMap::GameMap(sf::RenderWindow* window, int mapSX, int mapSY) {
	//сохран€ю переменные
	m_currentWindow = window;
	m_windowSizeX = (*window).getSize().x;
	m_windowSizeY = (*window).getSize().y;
	m_mapSizeX = mapSX;
	m_mapSizeY = mapSY;

	//масштабирую карту под размеры окна (Ќ≈ “–ќ√ј“№ ѕќ ј Ќ≈ —Ћќћј≈“—я)
	double rat = (double)m_mapSizeX / m_mapSizeY;

	m_mapOnScreenSizeX = (double)(m_windowSizeY * m_mapSizeX) / m_mapSizeY;
	m_mapOnScreenSizeY = (double)m_windowSizeY;
	
	if(m_mapOnScreenSizeX > m_windowSizeX || m_mapOnScreenSizeY > m_windowSizeY) {
		m_mapOnScreenSizeX = (double)m_windowSizeX;
		m_mapOnScreenSizeY = (double)(m_windowSizeX * m_mapSizeY) / m_mapSizeX;
	}


	//вычисл€ю размер тайла в пиксел€х
	tileSize = (float)m_mapOnScreenSizeX / m_mapSizeX;
	//очевидно
	m_vertexArray.setPrimitiveType(sf::Quads);

	//временный форскод, извин€юсь
	colorMap[0] = sf::Color::Magenta;
	colorMap[1] = sf::Color::White;
	colorMap[2] = sf::Color::Red;
	colorMap[3] = sf::Color::Green;
	colorMap[4] = sf::Color::Blue;
}
GameMap::~GameMap() {}

void GameMap::setMapSize(int sX, int sY) {
	m_map.resize(sX);
	for (int i = 0; i < m_map.size(); i++)
		m_map[i].resize(sY);
}
void GameMap::setMapSize() {
	m_map.resize(m_mapSizeX);
	for (int i = 0; i < m_map.size(); i++)
		m_map[i].resize(m_mapSizeY);
}

void GameMap::fillMap() {
	int col = rand() % 5;
	for (int ix = 0; ix < m_map.size(); ix++) {
		for (int iy = 0; iy < m_map[ix].size(); iy++) {
			col = rand() % 5;
			m_map[ix][iy] = col;
			//std::cout << "ix=" << ix << "\tiy=" << iy << "\tsizeX=" << m_map.size() << "\tsizeY=" << m_map[ix].size() << "color: " << col << std::endl;
		}
	}
}

void GameMap::fillVertexArray() {
	m_vertexArray.clear();
	int counter = 0;
	int offsetX = (m_windowSizeX - m_mapOnScreenSizeX) * 0.5;
	int offsetY = (m_windowSizeY - m_mapOnScreenSizeY) * 0.5;
	for (int ix = 0; ix < m_map.size(); ix++) {
		for (int iy = 0; iy < m_map[ix].size(); iy++) {
			counter++;
			addSqare(ix * tileSize + offsetX, iy * tileSize + offsetY, colorMap[m_map[ix][iy]]);
			//std::cout << "ix=" << ix << "\tiy=" << iy << "\tsizeX=" << m_map.size() << "\tsizeY=" << m_map[ix].size() << std::endl;
		}
	}
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

sf::VertexArray* GameMap::getVertexArray() {
	return &m_vertexArray;
}