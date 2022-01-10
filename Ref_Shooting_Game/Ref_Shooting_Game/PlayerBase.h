#pragma once
#include "Entity.h"
class PlayerBase :
    public Entity
{
public:
    PlayerBase();
    void DrawObject(HDC hdc);
    class BulletBase* Attack();
};

