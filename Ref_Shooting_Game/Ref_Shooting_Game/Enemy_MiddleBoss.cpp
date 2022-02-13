#include "Enemy_MiddleBoss.h"
#include "Bullet_Normal.h"
#include <iostream>
//움직이는거, 체력, 데미지
Enemy_MiddleBoss::Enemy_MiddleBoss()
{
	SetHealth(100);
	SetSize(150, 150);
	SetLocation(POINT{ 700,15 });
	flag = true;
}

bool Enemy_MiddleBoss::MoveNext()
{
	
	int type = 0;
	Location = POINT{ Location.x , Location.y };
	if(flag==true)
	{
		Location.x += 5;
	if (Location.x > 800)
		flag = false;
	}
	else
	{ 
			Location.x -= 5;
		if (Location.x < 500)
			flag = true;
	}
	// 맵밖으로 나가면 false 아닐경우 true 반환
	if (10 > Location.y || Location.y > 690) return false;
	else if (400 > Location.x || Location.x > 1000) return false;
	else return true;
}

BulletBase* Enemy_MiddleBoss::Attack()
{
	POINT location = GetLocation();

	// 중앙에서 Bullet 발사
	location.x += GetSize().x / 2 - 5 / 2;
	location.y += GetSize().y / 2 - 5 / 2;

	BulletBase* Bullet = new Bullet_Normal(location, POINTF{ 0, 5 });		//GetLocation() 은 현재 위치 x,y 좌표값, POINTF 는 총알 속도 지정														//newLocation, newVelocity
	Bullet->SetSize(10, 10);
	return Bullet;
}
void Enemy_MiddleBoss::DrawObject(HDC hdc)
{
	RECT temp = GetRect();
	Ellipse(hdc, temp.left, temp.top, temp.right, temp.bottom);
}