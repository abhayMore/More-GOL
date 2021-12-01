#include "../Header Files/Button.hpp"

Button::Button(std::string t, sf::Vector2f size, int charSize, sf::Color bgColor, sf::Color textColor)
{
	text.setString(t);
	text.setFillColor(textColor);
	text.setCharacterSize(charSize);

	button.setSize(size);
	button.setFillColor(bgColor);
}

void Button::setFont(sf::Font & font)
{
	text.setFont(font);
}

void Button::setBackColor(sf::Color color)
{
	button.setFillColor(color);
}

void Button::setTextColor(sf::Color color)
{
	text.setFillColor(color);
}

void Button::setPosition(sf::Vector2f pos)
{
	button.setPosition(pos);
	float xPos = (pos.x + button.getLocalBounds().width / 2) - (text.getLocalBounds().width / 2);
	float yPos = (pos.y + button.getLocalBounds().height / 3) - (text.getLocalBounds().height / 3);
	text.setPosition(sf::Vector2f(xPos, yPos));
}

void Button::draw(sf::RenderWindow & window)
{
	window.draw(button);
	window.draw(text);
}

bool Button::isMouseOver(sf::RenderWindow & window)
{
	float mouseX = sf::Mouse::getPosition(window).x;
	float mouseY = sf::Mouse::getPosition(window).y;

	float btnPosX = button.getPosition().x;
	float btnPosY = button.getPosition().y;

	float btnXPosWidth = button.getPosition().x + button.getLocalBounds().width;
	float btnYPosHeight = button.getPosition().y + button.getLocalBounds().height;

	if (mouseX < btnXPosWidth && mouseX > btnPosX && mouseY < btnYPosHeight && mouseY > btnPosY)
		return true;
	return false;
}

sf::Vector2f Button::getPosition()
{
	return button.getPosition();
}

void Button::setOutlineTextColor(sf::Color color)
{
	text.setOutlineColor(color);
}

void Button::setOutlineThickness(int size)
{
	text.setOutlineThickness(size);
}

