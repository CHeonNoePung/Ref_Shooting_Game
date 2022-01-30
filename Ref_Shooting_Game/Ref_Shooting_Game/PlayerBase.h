#pragma once
#include "Entity.h"
class PlayerBase :
    public Entity
{
public:
    PlayerBase();
    void DrawObject(HDC hdc);
    class BulletBase* Attack();
    void GetDamages(int x);
private:
    int Life;
    int PowerCount;
};

