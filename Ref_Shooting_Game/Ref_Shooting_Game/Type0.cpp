#include "Type0.h"
#include "EnemyBase.h"

Type0::Type0()
{
	SetHealth(5);
	SetSize(15, 15);
	test_sin = 0;
	
}

Type0::~Type0()
{
}

bool Type0::MoveNext()
{
	//Rectangle(hdc, 400, 10, 1000, 690) ȭ�� ������
	Location = POINT{ Location.x , Location.y };

	Location.x = 500 + sin(test_sin) * 45;
	Location.y += 5;
	test_sin += 1;


	// ȭ�� ���� ������ false �ƴϸ� true
	if (10 > Location.y || Location.y > 690) return false;
	else if (400 > Location.x || Location.x > 1000) return false;
	else return true;
}
