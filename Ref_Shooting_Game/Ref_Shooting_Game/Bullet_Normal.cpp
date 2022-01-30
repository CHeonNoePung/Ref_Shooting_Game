#include "Bullet_Normal.h"

void Bullet_Normal::DrawObject(HDC hdc)
{

	RECT temp = GetRect();
	Ellipse(hdc, temp.left, temp.top, temp.right, temp.bottom);
}

Bullet_Normal::Bullet_Normal(POINT newLocation, POINTF newVelocity) : BulletBase(newLocation,newVelocity)
{

}





