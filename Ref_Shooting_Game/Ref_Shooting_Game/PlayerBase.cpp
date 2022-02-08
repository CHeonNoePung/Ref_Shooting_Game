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
	timer = new Timer();
}

void PlayerBase::DrawObject(HDC hdc)
{
	RECT temp = GetRect();
	Rectangle(hdc, temp.left, temp.top, temp.right, temp.bottom);
}

BulletBase* PlayerBase::Attack()
{
	POINT location = GetLocation();		
	// �߾ӿ��� Bullet �߻�
	location.x += GetSize().x / 2 - 5 / 2;
	location.y += GetSize().y / 2 - 5 / 2;

	BulletBase* Bullet = new Bullet_Normal(location, POINTF{ 0,-5 });		//GetLocation() �� ���� ��ġ x,y ��ǥ��, POINTF �� �Ѿ� �ӵ� 
																				//newLocation, newVelocity
	Bullet->SetSize(5, 5);
	Bullet->SetPlayer();
	return Bullet;
}

bool PlayerBase::GetDamages(int x)
{
	if (inv == true)
	{
		//std::cout << "�����̶� ������X" << std::endl;
		return false;
	}
	bool bDead = false;
	int GetLife;
	GetLife = GetHealth() - x;
	if (GetLife < 1) 
	{
		Life = Life - 1;
		bDead = true;
		timer->TimerStart(*this, 5000, &PlayerBase::revive);
	}
	else 
	{
		// std::cout << "����ü�� : " << GetHealth() << std::endl;
		inv = true;
		// std::cout << "���� ����" << std::endl;
		timer->TimerStart(*this, 1000, &PlayerBase::inv_end);
		SetHealth(GetLife);
	}
	

	if (bDead == true) return true;		//������ true
	return false;
	
}

void PlayerBase::inv_end()
{
	std::cout << "���� ����" << std::endl;
	inv = false;
}

void PlayerBase::revive()
{
	inv = true;
	SetHealth(5);
	SetLocation(POINT{ 800,400 });
	timer->TimerStart(*this, 3000, &PlayerBase::inv_end);
	std::cout << "���� ���� 2" << std::endl;
}

