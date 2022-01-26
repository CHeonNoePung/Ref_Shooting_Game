#include "EnemyBase.h"
#include "Bullet_Normal.h"


EnemyBase::EnemyBase()
{
	SetLocation(POINT{ 500, 100 });
	SetHealth(1);
}

void EnemyBase::DrawObject(HDC hdc)
{
	int x = Location.x;
	int y = Location.y;
	Ellipse(hdc, x, y, x + 40, y + 40);
}

BulletBase* EnemyBase::Attack()
{
	BulletBase* Bullet = new Bullet_Normal(GetLocation(), POINTF{ 0, 3 });		//GetLocation() 은 현재 위치 x,y 좌표값, POINTF 는 총알 속도 지정
																				//newLocation, newVelocity

	return Bullet;
}

bool EnemyBase::MoveNext()
{
	Location = POINT{ Location.x , Location.y };

	if (Location.y < 0) return false;
	else if (Location.x < 0) return false;
	else return true;
}