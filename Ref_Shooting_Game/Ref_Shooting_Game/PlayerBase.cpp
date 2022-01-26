#include "PlayerBase.h"
#include "Bullet_Normal.h"


PlayerBase::PlayerBase()
{
	SetLocation(POINT{ 800,400 });
	SetHealth(5);// ü�� 5
	Life = 3;
	PowerCount = 3;
}

void PlayerBase::DrawObject(HDC hdc)
{
	int x = Location.x;
	int y = Location.y;
	Rectangle(hdc, x, y, x + 20, y + 20);
}

BulletBase* PlayerBase::Attack()
{
	BulletBase* Bullet = new Bullet_Normal(GetLocation(),POINTF{ 0,-5 });		//GetLocation() �� ���� ��ġ x,y ��ǥ��, POINTF �� �Ѿ� �ӵ� ����
																				//newLocation, newVelocity
	return Bullet;
}

void PlayerBase::GetDamages()
{
	int GetLife;
	GetLife = GetHealth() - 1;
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
	
}