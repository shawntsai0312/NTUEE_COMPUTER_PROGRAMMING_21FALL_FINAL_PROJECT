#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

enum button_states{BTN_IDLE=0,BTN_HOVER,BTN_ACTIVE};

class Button
{
private:
	int buttonState;

	sf::RectangleShape shape;
	sf::Text text;
	sf::Font* font;

	sf::Color textIdleColor;
	sf::Color textHoverColor;
	sf::Color textActiveColor;

	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;
public:
	Button(float x, float y, float width, float height, std::string text, sf::Font* font, int size,
		sf::Color textIdleColor, sf::Color textHoverColor, sf::Color textActiveColor,
		sf::Color idleColor, sf::Color hoverColor, sf::Color acitveColor);
	~Button();


	const bool isPressed() const;
	const float getXPosition() const;
	const float getYPosition() const;
	const float getWidth() const;
	const float getHeight() const;

	void update(const sf::Vector2f mousePos);
	void render(sf::RenderTarget* target);
};
