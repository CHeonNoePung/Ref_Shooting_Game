#pragma once
#include "Object.h"
class Entity :
    public Object
{
private :
    int Health;
public:
    int GetHealth();
    void SetHealth(int newHealth);

    virtual class BulletBase* Attack();

};



