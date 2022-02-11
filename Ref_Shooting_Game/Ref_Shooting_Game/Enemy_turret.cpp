#include "Enemy_turret.h"
#include "Bullet_Normal.h"

//�����̴°�, ü��, ������
Enemy_turret::Enemy_turret()
{
	SetHealth(10);
	SetSize(40, 40);
	SetLocation(POINT{ 700,20 });
}

bool Enemy_turret::MoveNext()
{
	Location = POINT{ Location.x , Location.y };
	Location.y += 1;
	// �ʹ����� ������ false �ƴҰ�� true ��ȯ
	if (10 > Location.y || Location.y > 690) return false;
	else if (400 > Location.x || Location.x > 1000) return false;
	else return true;
}

BulletBase* Enemy_turret::Attack()
{
	POINT location = GetLocation();

	// �߾ӿ��� Bullet �߻�
	location.x += GetSize().x / 2 - 5 / 2;
	location.y += GetSize().y / 2 - 5 / 2;

	BulletBase* Bullet = new Bullet_Normal(location, POINTF{ 0, 5 });		//GetLocation() �� ���� ��ġ x,y ��ǥ��, POINTF �� �Ѿ� �ӵ� ����														//newLocation, newVelocity
	Bullet->SetSize(5, 5);
	return Bullet;
}
void Enemy_turret::DrawObject(HDC hdc)
{
	RECT temp = GetRect();
	Ellipse(hdc, temp.left, temp.top, temp.right, temp.bottom);
}

