#include "PlayerBase.h"
#include "Bullet_Normal.h"


PlayerBase::PlayerBase()
{
	SetLocation(POINT{ 800,400 });
	SetHealth(5);// 체력 5
	Life = 3;
	PowerCount = 3;
	SetSize(21, 21);
	SetPlayer();
	inv = false;
}

void PlayerBase::DrawObject(HDC hdc)
{
	RECT temp = GetRect();
	Rectangle(hdc, temp.left, temp.top, temp.right, temp.bottom);
}

BulletBase* PlayerBase::Attack()
{
	POINT location = GetLocation();		
	// 중앙에서 Bullet 발사
	location.x += GetSize().x / 2 - 5 / 2;
	location.y += GetSize().y / 2 - 5 / 2;

	BulletBase* Bullet = new Bullet_Normal(location, POINTF{ 0,-5 });		//GetLocation() 은 현재 위치 x,y 좌표값, POINTF 는 총알 속도 
																				//newLocation, newVelocity
	Bullet->SetSize(5, 5);
	Bullet->SetPlayer();
	return Bullet;
}

void PlayerBase::GetDamages(int x)
{
	if (inv == true)
	{
		return;
	}

	int GetLife;
	GetLife = GetHealth() - x;
	if (GetLife < 1) 
	{
		Life = Life - 1;
		SetHealth(5);
		SetLocation(POINT{ 800,400 });
	
	}
	else 
	{
		SetHealth(GetLife);
	}
	
	inv = true;

	timer.TimerStart(*this, 1000, &PlayerBase::inv_end);
	
}

void PlayerBase::inv_end()
{
	inv = false;
}

