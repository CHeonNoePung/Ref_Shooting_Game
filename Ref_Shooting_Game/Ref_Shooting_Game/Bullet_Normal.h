#pragma once
#include "BulletBase.h"
class Bullet_Normal :
    public BulletBase
{
private:
    int choose_num;
public:
    void DrawObject(HDC hdc);
    Bullet_Normal(POINT newLocation, POINTF newVelocity, int aa);

};

