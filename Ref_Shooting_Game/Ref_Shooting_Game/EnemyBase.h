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
    void DrawObject(HDC hdc);
    class BulletBase* Attack();
    bool MoveNext();
    bool GetDamages(int x);
    int GetKeyCode();
};
