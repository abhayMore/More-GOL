#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>

#include <vector>

#include "../Header Files/FileSystem.hpp"
#include "../Header Files/FileSystem.hpp"

#include "../Header Files/Life.hpp"
#include "../Header Files/UI.hpp"

#define WIDTH 1200
#define HEIGHT 550

void drawCells(std::vector< std::vector <int> > &vec, sf::RenderWindow& window, int ROWS, int COLS, int Res, int offsetX = 0, int offsetY = 0, bool flag = false)
{
	int x, y;
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			sf::RectangleShape cells;
			if (flag)
			{
				x = offsetX + j * Res;
				y = offsetY + i * Res;
			}
			else
			{
				x = offsetX + i * Res;
				y = offsetY + j * Res;
			}
			if (vec[i][j] == 1)
			{
				cells.setFillColor(sf::Color::White);
				cells.setPosition(sf::Vector2f(x, y));
				cells.setSize(sf::Vector2f(Res - 1, Res - 1));
				window.draw(cells);
			}
			else if (vec[i][j] == 0)
			{
				cells.setFillColor(sf::Color::Black);
				cells.setPosition(sf::Vector2f(x, y));
				cells.setSize(sf::Vector2f(Res - 1, Res - 1));
				window.draw(cells);
			}
		}
	}
}

int main()
{
	srand(time(0));
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "GOL", sf::Style::Titlebar | sf::Style::Close, settings);
	window.setFramerateLimit(30);

	sf::Font Dosis;
	Dosis.loadFromFile("./Fonts/Dosis-Light.ttf");

	Life grid(window);
	grid.randomizeGrid();
	UI allUI(window, Dosis, grid);

	FileSystem PatternMatrixFile("./Config Files/patterns.ini");
	int r = 40;
	int c = 40;
	std::vector<std::vector<std::vector<int>>> allPatterns;
	allPatterns = PatternMatrixFile.getAllPatterns(allPatterns, r, c);

	FileSystem PatternNamesFile("./Config Files/Names.ini");
	std::vector<sf::Text> patternNames(allPatterns.size());
	patternNames = PatternNamesFile.getPatternNames(patternNames);
	for (int i = 0; i < patternNames.size(); i++)
	{
		patternNames[i].setFont(Dosis);
		patternNames[i].setCharacterSize(25);
		patternNames[i].setFillColor(sf::Color::White);
		patternNames[i].setOutlineThickness(2);
		patternNames[i].setOutlineColor(sf::Color::Magenta);
		patternNames[i].setStyle(sf::Text::Bold);
		patternNames[i].setOrigin(patternNames[i].getLocalBounds().width / 2.0f, patternNames[i].getLocalBounds().height / 2.0f);
		patternNames[i].setPosition(sf::Vector2f(810 + (1200 - 810) / 2, grid.getMenuLevels().y / 2));
	}

	bool start = false;
	bool mouseDraw = false;
	bool mouseErase = false;
	bool patternSelect = false;
	bool controlButtonPressed = false;
	bool mouseHovered = true;
	int nextValue = 0;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
			{
				window.close();
			}
			break;
			case sf::Event::Resized:
			{
				sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
				window.setView(sf::View(visibleArea));
			}
			break;

			case sf::Event::KeyPressed:
			{
				switch (event.key.code)
				{
				case sf::Keyboard::S:
				{
					if (start)
						start = false;
					else
						start = true;
				}
				break;
				case sf::Keyboard::T:
				{
					grid.changeGridPattern(allPatterns[nextValue]);
				}
				break;
				case sf::Keyboard::R:
				{
					grid.randomizeGrid();
				}
				break;
				case sf::Keyboard::N:
				{
					nextValue += 1;
					if (nextValue >= allPatterns.size())
						nextValue = 0;
				}
				break;
				case sf::Keyboard::C:
				{
					grid.clearGrid();
				}
				break;
				default:
					break;
				}
			}
			case sf::Event::MouseMoved:
			{
				mouseHovered = true;
			}
			break;
			case sf::Event::MouseButtonPressed:
			{
				switch (event.mouseButton.button) {
				case sf::Mouse::Left:
				{
					controlButtonPressed = true;
					mouseDraw = true;
					patternSelect = true;
				}
				break;
				case sf::Mouse::Right:
				{
					mouseErase = true;
				}
				break;
				default:
					break;
				}
			}
			break;
			case sf::Event::MouseButtonReleased:
			{
				switch (event.mouseButton.button) {
				case sf::Mouse::Left:
				{
					mouseDraw = false;
				}
				break;
				case sf::Mouse::Right:
				{
					mouseErase = false;
				}
				break;
				}
				break;
			default:
				break;
			}
			}
		}
		int clickedX = std::floor(sf::Mouse::getPosition(window).x / grid.getResolution());
		int clickedY = std::floor(sf::Mouse::getPosition(window).y / grid.getResolution());
		if (clickedX < grid.getRowsNCols().x && clickedY < grid.getRowsNCols().y)
		{
			if (mouseDraw)
				grid.changeGridState(clickedX, clickedY, 1);

			if (mouseErase)
				grid.changeGridState(clickedX, clickedY, 0);
		}
		if (controlButtonPressed)
		{
			allUI.mouseUIEvents(window, start, grid, allPatterns, nextValue);
			controlButtonPressed = false;
		}
		if (patternSelect)
		{
			sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));

			if (allUI.getSpriteBounds1().contains(mouse))
			{
				nextValue -= 1;
				if (nextValue < 0)
				{
					nextValue = allPatterns.size() - 1;
				}
			}
			if (allUI.getSpriteBounds2().contains(mouse))
			{
				nextValue += 1;
				if (nextValue >= allPatterns.size())
					nextValue = 0;
			}
			patternSelect = false;
		}
		if (mouseHovered)
		{
			allUI.mouseHoveredEvents(window);
			mouseHovered = false;
		}

		window.clear(sf::Color(105, 105, 105));
		if (start)
		{
			grid.calculateNextgen();
		}
		drawCells(grid.getGrid(), window, grid.getRowsNCols().x, grid.getRowsNCols().y, grid.getResolution());
		drawCells(allPatterns[nextValue], window, c, r, grid.getResolution(), window.getSize().x - grid.getMenuLevels().x + 10, grid.getMenuLevels().y, true);

		allUI.drawUI(window);
		window.draw(patternNames[nextValue]);
		window.display();
	}
	return 0;
}