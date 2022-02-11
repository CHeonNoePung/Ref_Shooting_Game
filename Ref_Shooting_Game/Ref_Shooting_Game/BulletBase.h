#pragma once
#include "Object.h"
class BulletBase :
    public Object
{
private:
    POINTF Velocity;
    static int g_KeyCode;
    int KeyCode;
    
public:
    BulletBase();
    BulletBase(POINT newLocation, POINTF newVelocity);
    bool MoveNext();                   
    void SetVelocity(POINTF pointf);
    POINTF GetVelocity();
    int GetKeyCode();

};

