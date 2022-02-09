#include "EnemyBase.h"
#include "Bullet_Normal.h"

// ����ƽ ������ ���⿡ ��
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
	0 == ���
	1 == �߰�����
	2 == ����
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
		printf(" EnemyBase���� �������� ���ڸ� �߸� �ο��� Ȯ���� ��");
	}
	printf("%d �� ������\n", KeyCode);
}


void EnemyBase::DrawObject(HDC hdc)
{
	RECT temp = GetRect();
	Ellipse(hdc, temp.left, temp.top, temp.right, temp.bottom);
}

BulletBase* EnemyBase::Attack()
{
	BulletBase* Bullet = new Bullet_Normal(GetLocation(), POINTF{ 0, 3 });		//GetLocation() �� ���� ��ġ x,y ��ǥ��, POINTF �� �Ѿ� �ӵ� ����														//newLocation, newVelocity
	Bullet->SetSize(5, 5);
	return Bullet;
}

bool EnemyBase::MoveNext()
{
	

	//Rectangle(hdc, 400, 10, 1000, 690)// ���� ���
	Location = POINT{ Location.x , Location.y };

	Location.x = 500 + sin(test_sin) * 150;
	Location.y += 5;
	test_sin += 0.1;
	





	
	// �� ����� ������� false�� �� ����
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