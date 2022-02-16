#include "PlayerBase.h"
#include "Bullet_Normal.h"
#include "BulletLaser.h"
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
	inv_Invisible = false;
	bDead = false;
	timer = new Timer<PlayerBase>();
}




void PlayerBase::DrawObject(HDC hdc)
{

	if (inv_Invisible == true || bDead == true) return;
	RECT temp = GetRect();
	Rectangle(hdc, temp.left, temp.top, temp.right, temp.bottom);

	HBRUSH red_brush = CreateSolidBrush(RGB(255, 0, 0));
	RECT health_rect = { 1030, 180, 1050 + (GetHealth() * 50) , 210 };
	FillRect(hdc, &health_rect, red_brush);
	SelectObject(hdc, red_brush);
	DeleteObject(red_brush);
}

PatternResult PlayerBase::Attack(int choose_num__)
{
	
	
	POINT location = GetLocation();		
	// 중앙에서 Bullet 발사
	location.x += GetSize().x / 2 - 5 / 2;
	location.y += GetSize().y / 2 - 5 / 2;

	BulletBase* Bullet = nullptr;
	if (choose_num__ == 1) Bullet = new Bullet_Normal(location, POINTF{ 0,-5 });		//일반형
	else 
	{
		//printf("%d------\n", Location.y);
		Bullet = new BulletLaser(location, POINTF{ 0,-10 });//관통형
	}
	

	Bullet->SetSize(5, 5);
	Bullet->SetPlayer();		// 플레이어 소유로 변경

	PatternResult result;
	result.Bullet = Bullet;
	result.Interval = 0;

	return result;
}

bool PlayerBase::GetDamages(int x)
{
	if (inv == true || bDead == true)
	{
		return false;
	}
	int GetLife;
	GetLife = GetHealth() - x;
	if (GetLife < 1) 
	{
		Life = Life - 1;
		bDead = true;
		cout << "죽음   남은 목숨 : " << Life << endl;
		timer->TimerStart(*this, 2000, &PlayerBase::revive);
	}
	else 
	{
		inv_start(1000);
		SetHealth(GetLife);
		cout << "남은 체력 : " << GetHealth() << endl;
	}
	
	if (Life == 0)
	{
		return true;

	}
	return false;
	
}


void PlayerBase::revive()
{
	inv_start(3000);
	SetHealth(5);
	bDead = false;
	SetLocation(POINT{ 800,400 });
	
}


// 무정동안 깜박이게 함
void PlayerBase::flicker()
{
	if (inv == false)
	{
		inv_Invisible = false;
		return;
	}

	if (inv_Invisible == true)
		inv_Invisible = false;
	else
		inv_Invisible = true;

	timer->TimerStart(*this, 50, &PlayerBase::flicker);
}


void PlayerBase::inv_end()
{
	inv = false;
}

void PlayerBase::inv_start(int time)
{
	inv = true;
	timer->TimerStart(*this, time, &PlayerBase::inv_end);
	flicker();
}

bool PlayerBase::IsDead()
{
	return bDead;
}