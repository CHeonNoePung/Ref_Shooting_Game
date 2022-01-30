#include "Object.h"

Object::Object() 
{
    SetSize(0, 0);
}

void Object::SetSize(int width, int height) 
{
    this->width = width;
    this->height = height;
}

RECT Object::GetRect() 
{
    RECT temp = { Location.x, Location.y, Location.x + width, Location.y + height };
    return temp;
}

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
