#include "PatternHurricane.h"
#include "Bullet_Normal.h"
#include <iostream>


PatternHurricane::PatternHurricane(int Interval, int size) : PatternBase(Interval, size)
{
	flag = false;
	degree = 0;
}

PatternResult PatternHurricane::Next(PatternParam Param)
{
	PatternResult result = { nullptr,0 };
	
	RECT rect = Param.EntityRect;
	int Distance = 50;

	int RealDegree = degree;
	if (flag == true)
	{
		RealDegree += 180;
		degree += 15;
		flag = false;
		result.Interval = BulletInterval;
	}
	else
	{
		flag = true;
		result.Interval = 0;
	}
	// �߾� ��ġ
	POINT location;
	location.x = rect.left + (rect.right - rect.left) / 2 - BulletSize/2;
	location.y = rect.top + (rect.bottom - rect.top) / 2 - BulletSize/2;

	// �Ѿ� ��ġ
	POINT BulletLoc = location;
	BulletLoc.y -= (int)(sin(RealDegree * (3.14 / 180)) * Distance) ;
	BulletLoc.x -= (int)(cos(RealDegree * (3.14 / 180)) * Distance);


	// �Ÿ�����
	POINT Dist_vec = { BulletLoc.x - location.x, BulletLoc.y - location.y };

	// �������� ( ���� )
	POINTF Unit_vec = { (float)Dist_vec.x / Distance, (float)Dist_vec.y / Distance };

	BulletBase* Bullet = new Bullet_Normal(BulletLoc, Unit_vec);
	Bullet->SetSize(BulletSize, BulletSize);
	result.Bullet = Bullet;


	if (RealDegree == 345) degree = 0;


	


	return result;
}

