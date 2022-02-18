#include "Enemy_Boss.h"
#include "Bullet_Normal.h"
#include "PatternFlower.h"
Enemy_Boss::Enemy_Boss()
{
	SetHealth(300);
	SetSize(450, 150);
	SetLocation(POINT{ 475,15 });
	flag = true;
	patternFlower = new PatternFlower(70, 15);
}

Enemy_Boss::~Enemy_Boss()
{
	delete patternFlower;
}

bool Enemy_Boss::MoveNext()
{

	int type = 0;
	Location = POINT{ Location.x , Location.y };
	if (flag == true)
	{
		Location.x += 5;
		if (Location.x > 525)
			flag = false;
	}
	else
	{
		Location.x -= 5;
		if (Location.x < 425)
			flag = true;
	}
	// 맵밖으로 나가면 false 아닐경우 true 반환
	RECT rect = GetRect();

	if (rect.top < 11) return false;
	else if (rect.bottom > 688) return false;
	else if (rect.right > 998) return false;
	else if (rect.left < 400) return false;
	else return true;
}

PatternResult Enemy_Boss::Attack(PatternParam Param)
{
	/*
	PatternResult result = Pattern->Next(Param);
	*/

	PatternResult result = patternFlower->Next(Param);

	return result;
}

void Enemy_Boss::DrawObject(HDC hdc)
{
	RECT temp = GetRect();
	Ellipse(hdc, temp.left, temp.top, temp.right, temp.bottom);
}