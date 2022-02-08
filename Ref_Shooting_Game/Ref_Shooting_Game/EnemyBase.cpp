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

void EnemyBase::DrawObject(HDC hdc)
{
	RECT temp = GetRect();
	Ellipse(hdc, temp.left, temp.top, temp.right, temp.bottom);
}

BulletBase* EnemyBase::Attack()
{
	POINT location = GetLocation();

	// 중앙에서 Bullet 발사
	location.x += GetSize().x / 2 - 5 / 2;
	location.y += GetSize().y / 2 - 5 / 2;

	BulletBase* Bullet = new Bullet_Normal(location, POINTF{ 0, 3 });		//GetLocation() 은 현재 위치 x,y 좌표값, POINTF 는 총알 속도 지정														//newLocation, newVelocity
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

// 피격 시 체력 감소
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