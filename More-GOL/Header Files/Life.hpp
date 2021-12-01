#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

class Life
{
public:
	std::vector<std::vector<int>> grid;
	int rows;
	int cols;

	int resolution;
	int menuLevelX;
	int menuLevelY;

public:
	Life(sf::RenderWindow&);

	void randomizeGrid();
	void clearGrid();
	void calculateNextgen();

	std::vector<std::vector<int>>& getGrid();

	void changeGridPattern(std::vector < std::vector<int > >& vec);
	void changeGridState(int X, int Y, int state);

	sf::Vector2f getMenuLevels();
	sf::Vector2f getRowsNCols();

	int getResolution();
};