#pragma once
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

class ResourceManager {
private:
	std::string m_path;
	
public:
	ResourceManager(std::string i_path);

	std::string loadStringFromFile(std::string i_path);

	std::string loadMap(std::string i_path);

};