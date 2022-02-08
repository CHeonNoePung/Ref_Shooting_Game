#pragma once
#include "Entity.h"
#include <iostream>
class EnemyBase :
    public Entity
{
private:
    static int g_KeyCode;
    int KeyCode;
    int EnemyScore;
public:
    EnemyBase();
    EnemyBase(int type, POINT location);
    void DrawObject(HDC hdc);
    class BulletBase* Attack();
    bool MoveNext();
    int GetKeyCode();
    bool GetDamages();
};
