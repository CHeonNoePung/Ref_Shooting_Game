#pragma once
#include "Entity.h"

class Timer;
class PlayerBase :
    public Entity
{
public:

    void inv_end(); // ���� ����
    void revive(); // ������ �Ҹ� �� ��Ȱ �� ȣ��
    PlayerBase();
    void DrawObject(HDC hdc);
    class BulletBase* Attack();
    bool GetDamages(int x);

    
private:
    Timer *timer; // Timer ��ü ����
    bool inv; //invincibility : ����
    int Life;
    int PowerCount;
};

