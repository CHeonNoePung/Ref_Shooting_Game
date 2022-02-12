#pragma once
#include "Object.h"
class BulletBase :
    public Object
{
private:
    POINTF Velocity;
    POINTF LocationF;
    float Speed;
    static int g_KeyCode;
    int KeyCode;
    
public:
    BulletBase();
    BulletBase(POINT newLocation, POINTF newVelocity);
    bool MoveNext();                    // ���ʰ��� false ��ȯ
    void SetVelocity(POINTF pointf);
    POINTF GetVelocity();
    int GetKeyCode();
    void SetSpeed(int newSpeed);
    

};

