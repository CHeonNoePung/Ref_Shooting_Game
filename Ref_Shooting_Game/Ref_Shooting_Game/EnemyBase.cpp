#include "EnemyBase.h"
#include "Bullet_Normal.h"

// 스태틱 변수라서 여기에 함
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
	test_sin = 0;
	this->type = type;
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
	printf("%d 개 생성됨\n", KeyCode);
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
	

	//Rectangle(hdc, 400, 10, 1000, 690)// 게임 배경
	Location = POINT{ Location.x , Location.y };

	Location.x = 500 + sin(test_sin) * 150;
	Location.y += 5;
	test_sin += 0.1;
	





	
	// 맵 벗어나면 사라지게 false면 몹 삭제
	if (10 > Location.y || Location.y > 690) return false;
	else if ( 400 > Location.x || Location.x > 1000 ) return false;
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