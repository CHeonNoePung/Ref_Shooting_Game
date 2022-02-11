#pragma once
#include "Entity.h"
#include <iostream>
#include "PatternBase.h"
class EnemyBase :
    public Entity
{
private:
    static int g_KeyCode;
    int KeyCode;
    int EnemyScore;
    PatternBase* Pattern;
public:
    EnemyBase();
    ~EnemyBase();

    void DrawObject(HDC hdc);
    virtual PatternResult Attack();
    bool MoveNext();
    bool GetDamages(int x);
    int GetKeyCode();
    float test_sin;
};
