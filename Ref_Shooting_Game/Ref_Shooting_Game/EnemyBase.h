#pragma once
#include "Entity.h"
class EnemyBase :
    public Entity

{

public:
    EnemyBase();
    void DrawObject(HDC hdc);
    class BulletBase* Attack();
    bool MoveNext();
};
