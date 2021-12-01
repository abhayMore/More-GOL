#include "../Header Files/UI.hpp"

UI::UI(sf::RenderWindow& window, sf::Font& font, Life grid)
{
	texture.loadFromFile("./Resource Files/arrow.png");
	allColor = sf::Color::White;
	hoverColor = sf::Color::Green;

	for (int i = 0; i < sizeof(controlButtons) / sizeof(controlButtons[0]); i++)
	{
		controlButtons[i] = Button(buttonNames[i], { 80, 30 }, 17, allColor, sf::Color::Black);
		controlButtons[i].setFont(font);
		controlButtons[i].setOutlineTextColor(sf::Color::Blue);
		controlButtons[i].setOutlineThickness(1);
	}
	controlButtons[0].setPosition({ 133 - 80 / 2, 505 });
	controlButtons[1].setPosition({ 266 + 133 - 80 / 2, 505 });
	controlButtons[2].setPosition({ 266 * 2 + 133 - 80 / 2, 505 });
	controlButtons[3].setPosition({ 810 + 195 - 80 / 2, 505 });

	for (int i = 0; i < sizeof(ArrowSprite) / sizeof(ArrowSprite[0]); i++)
	{
		ArrowSprite[i].setTexture(texture);
		ArrowSprite[i].setScale(0.09, 0.09);
		ArrowSprite[i].setOrigin(sf::Vector2f(texture.getSize().x / 2, texture.getSize().y / 2));
	}
	ArrowSprite[0].setPosition(sf::Vector2f(810 + (965 - 810) / 2, 505 + 15));
	ArrowSprite[1].setPosition(sf::Vector2f(1045 + (1200 - 1045) / 2, 505 + 15));
	ArrowSprite[1].setRotation(180);

	border[0].setPosition(sf::Vector2f(window.getSize().x - grid.getMenuLevels().x, 0));
	border[0].setSize(sf::Vector2f(10, window.getSize().y));
	border[1].setPosition(sf::Vector2f(0, window.getSize().y - grid.getMenuLevels().y));
	border[1].setSize(sf::Vector2f(window.getSize().x, 10));
}

void UI::mouseUIEvents(sf::RenderWindow& window, bool& start, Life & grid, std::vector<std::vector<std::vector<int>>>& allPatterns, int& indexValue)
{
	if (controlButtons[0].isMouseOver(window))
	{
		if (start)
			start = false;
		else
			start = true;
	}
	if (controlButtons[1].isMouseOver(window))
	{
		grid.randomizeGrid();
	}
	if (controlButtons[2].isMouseOver(window))
	{
		grid.clearGrid();
	}
	if (controlButtons[3].isMouseOver(window))
	{
		grid.changeGridPattern(allPatterns[indexValue]);
	}
}

void UI::mouseHoveredEvents(sf::RenderWindow& window)
{
	for (int i = 0; i < 4; i++)
	{
		if (controlButtons[i].isMouseOver(window))
		{
			controlButtons[i].setBackColor(hoverColor);
		}
		else
		{
			controlButtons[i].setBackColor(allColor);
		}
	}
}

sf::FloatRect UI::getSpriteBounds1()
{
	return ArrowSprite[0].getGlobalBounds();
}

sf::FloatRect UI::getSpriteBounds2()
{
	return ArrowSprite[1].getGlobalBounds();
}

void UI::drawUI(sf::RenderWindow & window)
{
	for (int i = 0; i < 4; i++)
	{
		controlButtons[i].draw(window);
	}
	window.draw(border[0]);
	window.draw(border[1]);
	window.draw(ArrowSprite[0]);
	window.draw(ArrowSprite[1]);
}

