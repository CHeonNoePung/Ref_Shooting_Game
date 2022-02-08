#pragma once
#include "Entity.h"
#include "Timer.h"

class PlayerBase :
    public Entity
{
public:
    void inv_end();
    PlayerBase();
    void DrawObject(HDC hdc);
    class BulletBase* Attack();
    void GetDamages(int x);
private:
    Timer timer; // Timer ��ü ����
    bool inv; //invincibility : ����
    int Life;
    int PowerCount;
};

