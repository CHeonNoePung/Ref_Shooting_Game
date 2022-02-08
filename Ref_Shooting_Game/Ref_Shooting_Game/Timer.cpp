#include "Timer.h"
#include <iostream>

using namespace std;

DWORD WINAPI Timer::TimerTR(LPVOID Param)
{
    TimerStruct* ts = (TimerStruct*)Param;

    Sleep(ts->sec);
    ts->func(ts->playerbase);

    delete ts;
    return 0;
}


void Timer::TimerStart(PlayerBase& object, int sec, function<void(PlayerBase&)> func)
{
 
 
        TimerStruct* ts = new TimerStruct{ object,sec,func };
        TimerHandle = CreateThread(NULL, 0, Timer::TimerTR, ts, 0, NULL);
 
}