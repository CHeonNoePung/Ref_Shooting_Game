#pragma once
#include "EnemyBase.h"
class Enemy_MiddleBoss :
    public EnemyBase
{
public:
    Enemy_MiddleBoss();
    bool MoveNext();
    BulletBase* Attack();
    void DrawObject(HDC hdc);
private:
    bool flag;
};

