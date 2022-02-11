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
    virtual void DrawObject(HDC hdc);
    virtual class BulletBase* Attack();
    virtual bool MoveNext();
    bool GetDamages(int x);
    int GetKeyCode();
 
    
    int type;
    float test_sin;
};
