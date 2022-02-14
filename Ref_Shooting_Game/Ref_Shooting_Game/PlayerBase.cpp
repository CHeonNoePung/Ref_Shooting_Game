#include "PlayerBase.h"
#include "Bullet_Normal.h"
#include "Timer.h"
#include <iostream>

PlayerBase::PlayerBase()
{
	SetLocation(POINT{ 800,400 });
	SetHealth(5);// 체력 5
	Life = 3;
	PowerCount = 3;
	SetSize(21, 21);
	SetPlayer();
	inv = false;
	timer = new Timer();
	choose_num = 0;
}

void PlayerBase::DrawObject(HDC hdc)
{
	RECT temp = GetRect();
	Rectangle(hdc, temp.left, temp.top, temp.right, temp.bottom);
}

BulletBase* PlayerBase::Attack(int choose_num__)
{
	
	choose_num = choose_num__;
	
	POINT location = GetLocation();		
	// 중앙에서 Bullet 발사
	location.x += GetSize().x / 2 - 5 / 2;
	location.y += GetSize().y / 2 - 5 / 2;

	BulletBase* Bullet = new Bullet_Normal(location, POINTF{ 0,-5 }, 1);		//GetLocation() 은 현재 위치 x,y 좌표값, POINTF 는 총알 속도 
																				//newLocation, newVelocity
	
	if (choose_num == 1)Bullet = new Bullet_Normal(location, POINTF{ 0,-5 }, 1);		//일반형
	else if (choose_num == 2) {
		//printf("%d------\n", Location.y);
		Bullet = new Bullet_Normal(location, POINTF{ 0,-10 }, 2);//관통형
	}
	

	Bullet->SetSize(5, 5);
	Bullet->SetPlayer();
	return Bullet;
}

bool PlayerBase::GetDamages(int x)
{
	if (inv == true)
	{
		//std::cout << "무적이라 데미지X" << std::endl;
		return false;
	}
	bool bDead = false;
	int GetLife;
	GetLife = GetHealth() - x;
	if (GetLife < 1) 
	{
		Life = Life - 1;
		bDead = true;
		timer->TimerStart(*this, 500, &PlayerBase::revive);
	}
	else 
	{
		// std::cout << "남은체력 : " << GetHealth() << std::endl;
		inv = true;
		// std::cout << "무적 시작" << std::endl;
		timer->TimerStart(*this, 1000, &PlayerBase::inv_end);
		SetHealth(GetLife);
	}
	
	if (bDead == true) return true;		//죽으면 true
	return false;
	
}

void PlayerBase::inv_end()
{
	std::cout << "무적 해제" << std::endl;
	inv = false;
}

void PlayerBase::revive()
{
	inv = true;
	SetHealth(5);
	SetLocation(POINT{ 800,400 });
	timer->TimerStart(*this, 3000, &PlayerBase::inv_end);
	std::cout << "무적 해제 2" << std::endl;
}

