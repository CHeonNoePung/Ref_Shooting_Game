#include "EnemyBase.h"
#include "Bullet_Normal.h"

int EnemyBase::g_KeyCode = 0;

EnemyBase::EnemyBase()
{
	SetLocation(POINT{ 500, 100 });
	SetHealth(5);
	EnemyScore = 500;
	KeyCode = g_KeyCode++;
}

EnemyBase::EnemyBase(int type, POINT location)
{
	/*
	0 == 잡몹
	1 == 중간보스
	2 == 보스
	*/
	if (type == 0) 
	{
		SetLocation(POINT{ location.x, location.y });
		SetHealth(5);
		EnemyScore = 500;
		KeyCode = g_KeyCode++;
		SetSize(40, 40);
	}
	else if(type == 1)
	{
		SetLocation(POINT{ location.x, location.y });
		SetHealth(10);
		EnemyScore = 1000;
		KeyCode = g_KeyCode++;
		SetSize(100, 100);
	}
	else if (type == 2)
	{
		SetLocation(POINT{ location.x, location.y });
		SetHealth(50);
		EnemyScore = 2000;
		KeyCode = g_KeyCode++;
		SetSize(200, 200);
	}
	else
	{
		printf(" EnemyBase에서 생성자의 인자를 잘못 부여함 확인할 것");
	}
}


void EnemyBase::DrawObject(HDC hdc)
{
	RECT temp = GetRect();
	Ellipse(hdc, temp.left, temp.top, temp.right, temp.bottom);
}

BulletBase* EnemyBase::Attack()
{
	BulletBase* Bullet = new Bullet_Normal(GetLocation(), POINTF{ 0, 3 });		//GetLocation() 은 현재 위치 x,y 좌표값, POINTF 는 총알 속도 지정														//newLocation, newVelocity
	Bullet->SetSize(5, 5);
	return Bullet;
}

bool EnemyBase::MoveNext()
{
	Location = POINT{ Location.x , Location.y };

	if (Location.y < 0) return false;
	else if (Location.x < 0) return false;
	else return true;
}

bool EnemyBase::GetDamages() 
{
	std::cout << GetHealth();
	int GetLife;
	GetLife = GetHealth() - 1;
	if (GetLife < 0)
		return false;
	else
	{
		SetHealth(GetLife);
		return true;
	}
}


int EnemyBase::GetKeyCode()
{
	return KeyCode;
}