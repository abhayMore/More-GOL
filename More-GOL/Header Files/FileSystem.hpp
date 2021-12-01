#pragma once
#include <string>
#include <sstream>
#include <fstream>
#include <SFML/Graphics.hpp>

class FileSystem
{
	std::string fileName;
	std::ifstream inFile;
	std::string line;
public:
	FileSystem(std::string fName);
	~FileSystem();

	std::vector<std::vector<std::vector<int > > >& getAllPatterns(std::vector<std::vector<std::vector<int > > >& allPatterns, int sizeX, int sizeY);
	std::vector<sf::Text>& getPatternNames(std::vector<sf::Text>& patternNames);
};