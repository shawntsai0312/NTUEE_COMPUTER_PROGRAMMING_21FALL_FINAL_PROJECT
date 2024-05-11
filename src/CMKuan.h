#pragma once
#include "Entity.h"
class CMKuan :
    public Entity
{
private:
    void initVaribles();
    void initComponents();
public:
    CMKuan(float x, float y, sf::Texture* texture);
    ~CMKuan();
};
