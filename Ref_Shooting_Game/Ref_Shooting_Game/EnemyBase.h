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
    virtual void DrawObject(HDC hdc);
    class BulletBase* Attack();
    virtual bool MoveNext();
    bool GetDamages(int x);
    int GetKeyCode();
    bool GetDamages();
    int type;
    float test_sin;
};
