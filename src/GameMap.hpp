#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "ResourceManager.hpp"


struct Tile {
public:
	Tile(std::string texName, ResourceManager& resMan);
	Tile();

	std::string texture;
	sf::Sprite sprite;
};


class GameMap
{
private:
	ResourceManager* m_resourceManager;
	sf::RenderWindow* m_window;

	std::vector< std::vector <Tile> > m_map;

	int m_windowSizeX, m_windowSizeY, m_mapSizeX, m_mapSizeY;
	float m_mapOnScreenSizeX, m_mapOnScreenSizeY;
	double tileSize;

	sf::VertexArray m_vertexArray;
	sf::RenderTexture m_renderTexture;
	sf::Sprite m_renderSprite;

	void addSqare(int posX, int posY, sf::Color color);
	void addSqare(int posX, int posY, std::string texName);
	void setMapSize(int sX, int sY);
	void generateRenderTextur();
public:
	GameMap(sf::RenderWindow* window, ResourceManager* i_resourceManager, int mapSX, int mapSY);
	~GameMap();

	void loadMapFromStr(std::string inMap);

	void addSqare(int posX, int posY, int sizeX, int sizeY, sf::Color color);

	void setMapSize();

	void draw();
	void draw(bool old);
	sf::VertexArray& getVertexArray();
};