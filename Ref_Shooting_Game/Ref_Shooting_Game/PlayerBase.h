#pragma once
#include "Entity.h"


template <typename T> 
class Timer;

class PlayerBase :
    public Entity
{
public:

    void inv_end(); // 무적 종료
    void revive(); // 라이프 소모 후 부활 시 호출
    PlayerBase();
    void DrawObject(HDC hdc);
    PatternResult Attack();
    bool GetDamages(int x);

    
private:
    Timer<PlayerBase> *timer; // Timer 객체 만듦
    bool inv; //invincibility : 무적
    int Life;
    int PowerCount;
};

