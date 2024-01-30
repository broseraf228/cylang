#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>


class GameMap
{
private:
	std::map<int, sf::Color> colorMap;

	sf::RenderWindow* m_window;
	sf::VertexArray m_vertexArray;

	int m_windowSizeX, m_windowSizeY, m_mapSizeX, m_mapSizeY;
	float m_mapOnScreenSizeX, m_mapOnScreenSizeY;
	double tileSize;

	std::vector< std::vector <int> > m_map;

	void addSqare(int posX, int posY, sf::Color color);
	void setMapSize(int sX, int sY);
public:
	GameMap(sf::RenderWindow* window, int mapSX, int mapSY);
	~GameMap();

	void loadMapFromStr(std::string inMap);

	void addSqare(int posX, int posY, int sizeX, int sizeY, sf::Color color);

	void setMapSize();

	void fillMap();

	void fillVertexArray();

	void draw();
	sf::VertexArray& getVertexArray();
};