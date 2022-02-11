#pragma once
#include "PatternBase.h"
class PatternHurricane :
    public PatternBase
{
public:
    PatternHurricane(int Interval, int size);
    PatternResult Next(RECT rect);
private:
    int degree;          // °¢µµ
    int flag;
};

