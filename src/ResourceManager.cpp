#include "ResourceManager.hpp"

ResourceManager::ResourceManager(std::string i_path)
{
	//������� ���� �� ��������� � ���� �� �����
	int i = i_path.length();
	while (i_path[i] != '/' && i_path[i] != '\\') {
		i_path.erase(i);
		i--;
	}
	//�������� ���� �� ����� ��������
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