#include "EnomyBase.h"
#include "Bullet_Normal.h"


EnomyBase::EnomyBase()
{
	SetLocation(POINT{ 800,50 });
	int health = 1;

}

void EnomyBase::DrawObject(HDC hdc)
{
	int x = Location.x;
	int y = Location.y;
	Ellipse(hdc, x, y, x + 40, y + 40);
}

BulletBase* EnomyBase::Enomy_Attack()
{
	BulletBase* Bullet = new Bullet_Normal(GetLocation(), POINTF{ 0,-5 });		//GetLocation() �� ���� ��ġ x,y ��ǥ��, POINTF �� �Ѿ� �ӵ� ����
																				//newLocation, newVelocity
	return Bullet;
}