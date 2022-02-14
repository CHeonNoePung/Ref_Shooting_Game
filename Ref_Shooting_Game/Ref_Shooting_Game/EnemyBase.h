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
    ~EnemyBase();

    void DrawObject(HDC hdc);
    virtual PatternResult Attack(PatternParam Param);
    bool MoveNext();
    bool GetDamages(int x);
    int GetKeyCode();
    float test_sin;
};
