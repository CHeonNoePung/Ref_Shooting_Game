#include "Object.h"

void Object::DrawObject(HDC hdc)
{

}

POINT Object::GetLocation()
{

    return Location;
}

void Object::SetLocation(POINT point)
{
    Location = point;
}
