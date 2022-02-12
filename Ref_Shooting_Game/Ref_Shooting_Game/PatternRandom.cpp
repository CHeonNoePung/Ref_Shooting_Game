#include "PatternRandom.h"
#include "Bullet_Normal.h"
#include <random>
#include <iostream>

using namespace std;

PatternRandom::PatternRandom(int Interval, int size) : PatternBase(Interval, size)
{
}

PatternResult PatternRandom::Next(PatternParam Param)
{
	PatternResult result = { nullptr,0 };

	RECT rect = Param.EntityRect;
	int Distance = 50;

	// ���� �غ�
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(0, 359);

	int Degree = dis(gen);

	result.Interval = BulletInterval;

	// �߾� ��ġ
	POINT location;
	location.x = rect.left + (rect.right - rect.left) / 2 - BulletSize / 2;
	location.y = rect.top + (rect.bottom - rect.top) / 2 - BulletSize / 2;

	// �Ѿ� ��ġ
	POINT BulletLoc = location;
	BulletLoc.y -= (int)(sin(Degree * (3.14 / 180)) * Distance);
	BulletLoc.x -= (int)(cos(Degree * (3.14 / 180)) * Distance);


	// �Ÿ�����
	POINT Dist_vec = { BulletLoc.x - location.x, BulletLoc.y - location.y };

	// �������� ( ���� )
	POINTF Unit_vec = { (float)Dist_vec.x / Distance, (float)Dist_vec.y / Distance };

	BulletBase* Bullet = new Bullet_Normal(BulletLoc, Unit_vec);
	Bullet->SetSize(BulletSize, BulletSize);
	result.Bullet = Bullet;






	return result;
}
