#pragma warning(disable:4828)
#include "Type0.h"
#include "EnemyBase.h"
#include "PatternNormal.h"
Type0::Type0()
{
	SetHealth(5);
	SetSize(15, 15);
	test_sin = 0;
	patternNormal = new PatternNormal(500, 7);
}

Type0::~Type0()
{
	delete patternNormal;
}

bool Type0::MoveNext()
{
	//Rectangle(hdc, 400, 10, 1000, 690) 화면 사이즈
	Location = POINT{ Location.x , Location.y };

	Location.x = 500 + sin(test_sin) * 45;
	Location.y += 5;
	test_sin += 1;


	// 화면 범위 나가면 false 아니면 true
	RECT rect = GetRect();

	if (rect.top < 11) return false;
	else if (rect.bottom > 688) return false;
	else if (rect.right > 998) return false;
	else if (rect.left < 400) return false;
	else return true;
}

PatternResult Type0::Attack(PatternParam Param)
{
	/*
	PatternResult result = Pattern->Next(Param);
	*/
	PatternResult result = patternNormal->Next(Param);
	return result;
}