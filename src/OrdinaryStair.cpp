#include "OrdinaryStair.h"

OrdinaryStair::OrdinaryStair()
{
}

OrdinaryStair::OrdinaryStair(float x, float y, sf::Texture* texture)
{
	this->createSprite(texture);
	this->setPosition(x, y);
}

OrdinaryStair::~OrdinaryStair()
{
}
