#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class Entity
{
private:
	void initVariables();

protected:
	sf::Texture* texture;
	sf::Sprite* sprite;

	float movementSpeed;

public:
	Entity();
	~Entity();

	void createSprite(sf::Texture* texture);
	void changeTexture(sf::Texture* texture);

	virtual void setPosition(const float x, const float y);
	virtual const float getXPosition() const;
	virtual const float getYPosition() const;
	virtual void move(const float& dt, const float x, const float y);

	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* target);
};

