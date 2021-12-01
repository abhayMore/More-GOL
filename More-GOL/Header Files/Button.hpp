#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Button
{
private:
	sf::RectangleShape button;
	sf::Text text;
public:
	Button() {}
	Button(std::string t, sf::Vector2f size, int charSize, sf::Color bgColor, sf::Color textColor);

	void setFont(sf::Font &font);
	void setBackColor(sf::Color color);
	void setTextColor(sf::Color color);
	void setPosition(sf::Vector2f pos);
	void draw(sf::RenderWindow &window);

	bool isMouseOver(sf::RenderWindow &window);

	sf::Vector2f getPosition();

	void setOutlineTextColor(sf::Color color);
	void setOutlineThickness(int size);
};