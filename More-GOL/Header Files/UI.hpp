#pragma once
#include "Button.hpp"
#include "Life.hpp"

class UI : public Button
{
private:
	sf::Color allColor;
	sf::Color hoverColor;

	Button controlButtons[4];
	std::string buttonNames[4] = { "Start/Pause", "Randomize", "Clear", "Select" };

	sf::Texture texture;
	sf::Sprite ArrowSprite[2];

	sf::RectangleShape border[2];
public:
	UI(sf::RenderWindow& window, sf::Font& font, Life grid);

	void mouseUIEvents(sf::RenderWindow& window, bool& start, Life& grid, std::vector<std::vector<std::vector<int>>>& allPatterns, int& indexValue);
	void mouseHoveredEvents(sf::RenderWindow& window);

	sf::FloatRect getSpriteBounds1();
	sf::FloatRect getSpriteBounds2();

	void drawUI(sf::RenderWindow& window);
};


