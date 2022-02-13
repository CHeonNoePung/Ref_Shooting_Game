#include "Stage.h"
#include "Type0.h"

/*
 Rectangle(hdc, 400, 10, 1000, 690)// ���� ���

 ���� �ڵ鷯�� ��� ������ �� ������ ����(����, �÷��̾�, �Ѿ˿� ���� ���� ����)

 �� ���¿��� ���������� Ŭ������ ���� ������� �����۰Ÿ��� �Ÿ����� ��� ������
 �������� Ŭ���� �ȿ� GameHandler�� �ִ� �� �ۿ� ���ٴ� ������ ��
 �̷���� ���������� Ŭ������ ���� ����� �ǹ̰� ���� �׳� GameHandler�� �ϳ��� ����������
 GameHandler �ȿ� �������̶� ��� �߰��ϸ� �����°���


 ����,
 ���������� Ŭ������ ������ϸ� ����, �÷��̾�, �Ѿ����� ���� Ŭ������ �����ΰ�
 �������� �ȿ��� new�� �ҷ��� �ؾߵɰ� ����


*/

Stage::Stage()
{
	Monster_Number = 0;
}

Stage::~Stage()
{
	
}


EnemyBase* Stage::getMonsterBase()
{
	EnemyBase* Enemy = nullptr;
	// case �ڿ� ���ڰ� ������ ���� ������ ������ ��ȯ�ϰ� ������ case 0,1�� ���������� �θ� ��
	// ��ȯ�� ���� �޸��� �����ϸ� ��
	switch(Monster_Number)
	{
	case 0:
	{
	//new ������;
	Enemy = new EnemyBase();
	Sleep(1000);
	}
	break;
	case 1:
	{
	//new �ʷϹ���;
	Enemy = new EnemyBase();
	Sleep(500);
	}
	break;
	case 2: 
	{
	//new �ִϾ�߷� 
	Enemy = new Type0(); // ����
	Enemy->SetLocation(POINT{ 750,70 }); // ��ǥ ����
	Sleep(100);
	}
	break;
	default:
		printf("Stage Ŭ������ getMonsterBase �Լ����� ���������� �۵� ����");
		break;
	}
	Monster_Number++;

	return Enemy;
}
