#include "..\Header Files\Life.hpp"


int ReturnIntRandom(int lower, int upper)
{
	return (rand() % (upper - lower + 1)) + lower;
}

Life::Life(sf::RenderWindow& window) : resolution(10)
{
	resolution = 10;
	menuLevelX = 410;
	menuLevelY = 70;
	rows = (window.getSize().x - menuLevelX) / resolution;
	cols = (window.getSize().y - menuLevelY) / resolution;
	grid.resize(rows, std::vector<int>(cols));
}

void Life::randomizeGrid()
{
	for (int i = 0; i < grid.size(); i++)
	{
		for (int j = 0; j < grid[i].size(); j++)
		{
			grid[i][j] = ReturnIntRandom(0, 1);
		}
	}
}

void Life::clearGrid()
{
	for (size_t y = 0; y < grid.size(); y++)
	{
		for (size_t x = 0; x < grid[y].size(); x++)
		{
			grid[y][x] = '\0';
		}
	}
}

void Life::calculateNextgen()
{
	std::vector< std::vector<int>> next(rows, std::vector<int>(cols));
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			int sum = 0;
			for (int x = -1; x < 2; x++)
			{
				for (int y = -1; y < 2; y++)
				{
					int row = (x + i + rows) % rows;
					int col = (y + j + cols) % cols;
					sum += grid[row][col];
				}
			}
			sum -= grid[i][j];
			int state = grid[i][j];
			if (state == 0 && sum == 3)
			{
				next[i][j] = 1;
			}
			else if (state == 1 && (sum < 2 || sum > 3))
			{
				next[i][j] = 0;
			}
			else
			{
				next[i][j] = grid[i][j];
			}
		}
	}
	grid = next;
}

std::vector<std::vector<int>>& Life::getGrid()
{
	return grid;
}

void Life::changeGridPattern(std::vector<std::vector<int>>& vec)
{
	clearGrid();
	for (int i = 0; i < vec.size(); i++)
	{
		for (int j = 0; j < vec[i].size(); j++)
		{
			grid[j + 8][i + 8] = vec[i][j];
		}
	}
}

void Life::changeGridState(int X, int Y, int state)
{
	grid[X][Y] = state;
}

sf::Vector2f Life::getMenuLevels()
{
	return sf::Vector2f(menuLevelX, menuLevelY);
}

sf::Vector2f Life::getRowsNCols()
{
	return sf::Vector2f(rows, cols);
}

int Life::getResolution()
{
	return resolution;
}