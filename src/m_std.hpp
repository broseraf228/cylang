#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
std::vector<std::string> splitString(std::string str, char splitter);
std::string readFile(const std::string& fileName);