#pragma once
#include "Object.h"
#include "PatternBase.h"
class Entity :
    public Object
{
private :
    int Health;
public:
    int GetHealth();
    void SetHealth(int newHealth);
    virtual bool GetDamages(int x);
    virtual PatternResult Attack() = 0;

};



