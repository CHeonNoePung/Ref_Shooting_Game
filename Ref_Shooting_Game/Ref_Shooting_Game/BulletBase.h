#pragma once
#include "Object.h"
class BulletBase :
    public Object
{
private:
    POINTF Velocity;
public:
    BulletBase();
    BulletBase(POINT newLocation, POINTF newVelocity);
    bool MoveNext();                    // ���ʰ��� false ��ȯ
    void SetVelocity(POINTF pointf);
    POINTF GetVelocity();

};

