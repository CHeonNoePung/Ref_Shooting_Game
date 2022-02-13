#pragma once
#include "Entity.h"


template <typename T> 
class Timer;

class PlayerBase :
    public Entity
{
public:

    void inv_end(); // ���� ����
    void inv_start(int time);
    bool IsDead();
    // ���� ����
    void revive(); // ������ �Ҹ� �� ��Ȱ �� ȣ��
    void flicker(); // ������ ������
    PlayerBase();
    void DrawObject(HDC hdc);
    PatternResult Attack();
    bool GetDamages(int x);

    
private:
    Timer<PlayerBase> *timer; // Timer ��ü ����
    bool inv; //invincibility : ����
    int Life;
    int PowerCount;
    bool inv_Invisible;
    
    bool bDead;
};

