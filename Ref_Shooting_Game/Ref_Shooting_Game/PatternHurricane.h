#pragma once
#include "PatternBase.h"
class PatternHurricane :
    public PatternBase
{
public:
    PatternHurricane(int Interval, int size);
    PatternResult Next(PatternParam Param);
private:
    int degree;          // °¢µµ
    int flag;
};

