#include "..\Header Files\FileSystem.hpp"
#include <iostream>

FileSystem::FileSystem(std::string fName) : fileName(fName)
{
	line = "";
}

FileSystem::~FileSystem()
{
}

std::vector<std::vector<std::vector<int > > >& FileSystem::getAllPatterns(std::vector<std::vector<std::vector<int > > >& allPatterns, int sizeX, int sizeY)
{
	std::vector<std::vector<int>> patternMatrix(sizeX, std::vector<int>(sizeY));
	std::string temp = "";
	inFile.open(fileName);
	if (inFile.is_open())
	{
		int k = 0;
		int j = 0;
		while (getline(inFile, line))
		{
			if (line != "")
			{
				j = 0;
				line = line + ',';
				for (int i = 0; i < line.length(); i++)
				{
					if (line[i] != ',')
						temp += line[i];
					else
					{
						patternMatrix[k][j] = std::stoi(temp);
						temp = "";
						j++;
					}
				}
			}
			k++;
			if (line.length() == 0)
			{
				allPatterns.push_back(patternMatrix);
				patternMatrix.clear();
				k = 0;
				patternMatrix.resize(sizeX, std::vector<int>(sizeY));
			}
		}
	}
	else
		std::cout << "Failed to Load Patterns File" << std::endl;
	inFile.close();
	return allPatterns;
}

std::vector<sf::Text>& FileSystem::getPatternNames(std::vector<sf::Text>& patternNames)
{

	inFile.open(fileName);
	int i = 0;
	if (inFile.is_open())
	{
		while (!inFile.eof())
		{
			getline(inFile, line);
			patternNames[i].setString(line);
			i++;
		}
		inFile.close();
	}
	else
		std::cout << "Failed to Load Pattern Names File" << std::endl;
	return patternNames;
}