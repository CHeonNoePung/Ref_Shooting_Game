#include "Object.h"

Object::Object() 
{
    SetSize(0, 0);
    bPlayer = false;
}

void Object::SetSize(int width, int height) 
{
    this->width = width;
    this->height = height;
}

POINT Object::GetSize()
{
    return POINT{width, height};
}

RECT Object::GetRect() 
{
    RECT temp = { Location.x, Location.y, Location.x + width, Location.y + height };
    return temp;
}
RECT Object::GetRect_a()
{
    RECT temp;
    static int abc = 0;

    if (abc == 0) abc = Location.y;
    temp = { Location.x, Location.y, Location.x + width, abc };
    if (Location.y <= 10) abc = 0;

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


bool Object::IsPlayer()
{
    return bPlayer;
}

void Object::SetPlayer()
{
    bPlayer = true;
}