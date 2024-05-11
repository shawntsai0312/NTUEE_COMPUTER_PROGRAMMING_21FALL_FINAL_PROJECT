#include "CMKuan.h"

void CMKuan::initVaribles()
{
}

void CMKuan::initComponents()
{
}

CMKuan::CMKuan(float x, float y, sf::Texture* texture)
{
	this->initVaribles();
	this->initComponents();
	this->createSprite(texture);
	this->setPosition(x, y);
}

CMKuan::~CMKuan()
{
}
