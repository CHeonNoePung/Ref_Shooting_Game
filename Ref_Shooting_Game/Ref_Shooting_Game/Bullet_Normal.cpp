#include "Bullet_Normal.h"

void Bullet_Normal::DrawObject(HDC hdc)
{
	int x = Location.x;
	int y = Location.y;
	Ellipse(hdc, x, y, x + 10, y + 10);
}

Bullet_Normal::Bullet_Normal(POINT newLocation, POINTF newVelocity) : BulletBase(newLocation,newVelocity)
{

}





