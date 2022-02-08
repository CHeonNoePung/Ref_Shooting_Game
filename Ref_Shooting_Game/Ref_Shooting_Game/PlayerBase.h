#pragma once
#include "Entity.h"

class Timer;
class PlayerBase :
    public Entity
{
public:
    void inv_end();
    PlayerBase();
    void DrawObject(HDC hdc);
    class BulletBase* Attack();

    bool GetDamages(int x);
    
private:
    Timer *timer; // Timer °´Ã¼ ¸¸µê
    bool inv; //invincibility : ¹«Àû
    int Life;
    int PowerCount;
};

