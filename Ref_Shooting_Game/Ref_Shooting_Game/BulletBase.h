#pragma once
#include "Object.h"


template<typename T>
class Timer;

class BulletBase :
    public Object
{
private:
    POINTF Velocity;
    POINTF LocationF;
    float Speed;
    static int g_KeyCode;
    int KeyCode;
    bool bMoveStop;
    Timer<BulletBase>* timer;
    
public:
    BulletBase();
    ~BulletBase();
    BulletBase(POINT newLocation, POINTF newVelocity);
    bool MoveNext();                   
    void SetVelocity(POINTF pointf);
    POINTF GetVelocity();
    int GetKeyCode();
    void SetSpeed(int newSpeed);

    void StopMoving(int second);
    void WakeUp();
    

};

