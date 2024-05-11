#pragma once
#include "Entity.h"
class OrdinaryStair :
    public Entity
{
public:
    OrdinaryStair();
    OrdinaryStair(float x, float y, sf::Texture* texture);
    ~OrdinaryStair();

    
};

