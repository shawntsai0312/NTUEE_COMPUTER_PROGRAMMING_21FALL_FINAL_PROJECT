#include "Entity.h"

void Entity::initVariables()
{
	this->sprite = NULL;
	this->texture = NULL;
	this->movementSpeed = 100.f;
}

Entity::Entity()
{
	this->initVariables();
}

Entity::~Entity()
{
	delete this->sprite;
}

void Entity::createSprite(sf::Texture* texture)
{
	this->texture = texture;
	this->sprite = new sf::Sprite(*this->texture);
}

void Entity::changeTexture(sf::Texture* texture)
{
	this->texture = texture;
	this->sprite->setTexture(*this->texture);
}

void Entity::setPosition(const float x, const float y)
{
	if (this->sprite)
	{
		this->sprite->setPosition(x , y);
	}
}

const float Entity::getXPosition() const
{
	return this->sprite->getPosition().x;
}

const float Entity::getYPosition() const
{
	return this->sprite->getPosition().y;
}

void Entity::move(const float& dt, const float x, const float y)
{
	if (this->sprite)
	{
		this->sprite->move(x * this->movementSpeed * dt, y * this->movementSpeed * dt);
	}
}

void Entity::update(const float& dt)
{

}

void Entity::render(sf::RenderTarget* target)
{
	if (this->sprite)
	{
		//std::cout << "now rendering cm kuan\n";
		target->draw(*this->sprite);
	}
}

