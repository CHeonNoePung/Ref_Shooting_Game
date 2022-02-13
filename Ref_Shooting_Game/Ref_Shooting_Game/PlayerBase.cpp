#include "PlayerBase.h"
#include "Bullet_Normal.h"
#include "Timer.h"
#include <iostream>

PlayerBase::PlayerBase()
{
	SetLocation(POINT{ 800,400 });
	SetHealth(5);// ü�� 5
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
}

PatternResult PlayerBase::Attack()
{
	POINT location = GetLocation();		
	// �߾ӿ��� Bullet �߻�
	location.x += GetSize().x / 2 - 5 / 2;
	location.y += GetSize().y / 2 - 5 / 2;

	BulletBase* Bullet = new Bullet_Normal(location, POINTF{ 0,-5 });		//GetLocation() �� ���� ��ġ x,y ��ǥ��, POINTF �� �Ѿ� �ӵ� 
																				//newLocation, newVelocity
	Bullet->SetSize(5, 5);
	Bullet->SetPlayer();		// �÷��̾� ������ ����

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
		cout << "����   ���� ��� : " << Life << endl;
		timer->TimerStart(*this, 3000, &PlayerBase::revive);
	}
	else 
	{
		inv_start(1000);
		SetHealth(GetLife);
		cout << "���� ü�� : " << GetHealth() << endl;
	}
	

	if (bDead == true) return true;		//������ true
	return false;
	
}


void PlayerBase::revive()
{
	inv_start(3000);
	SetHealth(5);
	bDead = false;
	SetLocation(POINT{ 800,400 });
	
}


// �������� �����̰� ��
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