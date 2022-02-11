#pragma once
#include "Object.h"
class BulletBase :
    public Object
{
private:
    POINTF Velocity;
    POINTF LocationF;
    static int g_KeyCode;
    int KeyCode;
    
public:
    BulletBase();
    BulletBase(POINT newLocation, POINTF newVelocity);
    bool MoveNext();                    // 맵초과시 false 반환
    void SetVelocity(POINTF pointf);
    POINTF GetVelocity();
    int GetKeyCode();

};

