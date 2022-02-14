#include "Bullet_Normal.h"

void Bullet_Normal::DrawObject(HDC hdc)
{

	RECT temp;
	if (choose_num == 1) {
		temp = GetRect();
		Ellipse(hdc, temp.left, temp.top, temp.right, temp.bottom);
	}
	else {
		temp = GetRect_a();
		Rectangle(hdc, temp.left, temp.top, temp.right, temp.bottom);
	}

}

Bullet_Normal::Bullet_Normal(POINT newLocation, POINTF newVelocity, int aa) : BulletBase(newLocation, newVelocity)
{
	choose_num = aa;
}


