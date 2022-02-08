#pragma once

#include "windows.h"
#include <functional>
#include "PlayerBase.h"

using namespace std;
class Timer;

struct TimerStruct
{
    PlayerBase& playerbase;
    int sec;
    function<void(PlayerBase&)> func;
};



class Timer
{
private:
    HANDLE TimerHandle;
public:
    static DWORD WINAPI TimerTR(LPVOID Param);
    void TimerStart(PlayerBase& playerbase, int sec, function<void(PlayerBase&)> func);

};