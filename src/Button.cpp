#include "Button.h"

Button::Button(float x,float y, float width, float height, std::string text, sf::Font* font, int size, 
			sf::Color textIdleColor, sf::Color textHoverColor, sf::Color textActiveColor,
			sf::Color idleColor, sf::Color hoverColor, sf::Color acitveColor)
{
	this->buttonState = BTN_IDLE;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setFillColor(idleColor);

	this->font = font;
	this->text.setString(text);
	this->text.setFont(*this->font);
	this->text.setFillColor(textIdleColor);
	this->text.setCharacterSize(size);
	this->text.setPosition(
		this->shape.getPosition().x + this->shape.getGlobalBounds().width / 2.f - this->text.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y + this->shape.getGlobalBounds().height / 2.f - this->text.getGlobalBounds().height / 2.f - 10
	);

	this->textIdleColor = textIdleColor;
	this->textHoverColor = textHoverColor;
	this->textActiveColor = textActiveColor;

	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = acitveColor;

}

Button::~Button()
{
	
}

const bool Button::isPressed() const
{
	if (this->buttonState == BTN_ACTIVE)
		return true;
	return false;
}

const float Button::getXPosition() const
{
	return this->shape.getPosition().x;
}

const float Button::getYPosition() const
{
	return this->shape.getPosition().y;
}

const float Button::getWidth() const
{
	return this->shape.getSize().x;
}

const float Button::getHeight() const
{
	return this->shape.getSize().y;
}

void Button::update(const sf::Vector2f mousePos)
{
	//Idle
	this->buttonState = BTN_IDLE;

	if (this->shape.getGlobalBounds().contains(mousePos))
	{
		//Hover
		this->buttonState = BTN_HOVER;

		//Active
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->buttonState = BTN_ACTIVE;
		}
	}

	switch (buttonState)
	{
	case BTN_IDLE:
	{
		this->shape.setFillColor(this->idleColor);
		this->text.setFillColor(this->textIdleColor);
		break;
	}
	case BTN_HOVER:
	{
		this->shape.setFillColor(this->hoverColor);
		this->text.setFillColor(this->textHoverColor);
		break;
	}
	case BTN_ACTIVE:
	{
		this->shape.setFillColor(this->activeColor);
		this->text.setFillColor(this->textActiveColor);
		break;
	}
	default:
		break;
	}
}

void Button::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
	target->draw(this->text);
}
