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
    POINT monster_move[5] = { {450,15},{550,20},{600,25},{650,30},{700,35} };

public:
    EnemyBase();
    EnemyBase(int type, POINT location);
    virtual void DrawObject(HDC hdc);
    class BulletBase* Attack();
    virtual bool MoveNext();
    bool GetDamages(int x);
    int GetKeyCode();
    bool GetDamages();
    int type;
    float test_sin;
};
