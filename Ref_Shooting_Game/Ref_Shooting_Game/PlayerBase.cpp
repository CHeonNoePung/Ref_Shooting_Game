#include "PlayerBase.h"
#include "Bullet_Normal.h"


PlayerBase::PlayerBase()
{
	SetLocation(POINT{ 800,400 });
}

void PlayerBase::DrawObject(HDC hdc)
{
	int x = Location.x;
	int y = Location.y;
	Rectangle(hdc, x, y, x + 20, y + 20);
}

BulletBase* PlayerBase::Attack()
{
	BulletBase* Bullet = new Bullet_Normal(GetLocation(),POINTF{ 0,-5 });		//GetLocation() 은 현재 위치 x,y 좌표값, POINTF 는 총알 속도 지정
																				//newLocation, newVelocity
	return Bullet;
}
