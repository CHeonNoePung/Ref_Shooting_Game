#include "PatternNormal.h"
#include "Bullet_Normal.h"

PatternNormal::PatternNormal(int Interval, int size) : PatternBase(Interval, size)
{
}

PatternResult PatternNormal::Next(RECT rect)
{
	PatternResult result;


	// ���߾� ��ġ ���
	POINT location;
	location.x = rect.left + (rect.right - rect.left) / 2 - BulletSize / 2;
	location.y = rect.top + (rect.bottom - rect.top) / 2 - BulletSize / 2;

	BulletBase* Bullet = new Bullet_Normal(location, POINTF{ 0, 3 });		//GetLocation() �� ���� ��ġ x,y ��ǥ��, POINTF �� �Ѿ� �ӵ� ����														//newLocation, newVelocity
	Bullet->SetSize(BulletSize, BulletSize);

	result.Bullet = Bullet;
	result.Interval = BulletInterval;

	return result;
}

