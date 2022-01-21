#include "EnomyBase.h"
#include "Bullet_Normal.h"


EnomyBase::EnomyBase()
{
	SetLocation(POINT{ 800,50 });
	SetHealth(1);
}

void EnomyBase::DrawObject(HDC hdc)
{
	int x = Location.x;
	int y = Location.y;
	Ellipse(hdc, x, y, x + 40, y + 40);
}

BulletBase* EnomyBase::Attack()
{
	BulletBase* Bullet = new Bullet_Normal(GetLocation(), POINTF{ 0, 3 });		//GetLocation() 은 현재 위치 x,y 좌표값, POINTF 는 총알 속도 지정
																				//newLocation, newVelocity

	return Bullet;
}