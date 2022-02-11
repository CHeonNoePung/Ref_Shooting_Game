#pragma once
#include "PatternBase.h"
class PatternNormal :
    public PatternBase
{
    
public:
    PatternNormal(int Interval, int size);
    PatternResult Next(RECT rect);
};

