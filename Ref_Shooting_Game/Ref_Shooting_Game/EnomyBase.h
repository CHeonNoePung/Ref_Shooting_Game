#pragma once
#include "Entity.h"
class EnomyBase :
    public Entity

{

public:
    EnomyBase();
    void DrawObject(HDC hdc);
    class BulletBase* Attack();
};
