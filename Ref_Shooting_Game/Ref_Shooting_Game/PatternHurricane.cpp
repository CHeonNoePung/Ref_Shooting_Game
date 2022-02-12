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
	// Áß¾Ó À§Ä¡
	POINT location;
	location.x = rect.left + (rect.right - rect.left) / 2 - BulletSize/2;
	location.y = rect.top + (rect.bottom - rect.top) / 2 - BulletSize/2;

	// ÃÑ¾Ë À§Ä¡
	POINT BulletLoc = location;
	BulletLoc.y -= (int)(sin(RealDegree * (3.14 / 180)) * Distance) ;
	BulletLoc.x -= (int)(cos(RealDegree * (3.14 / 180)) * Distance);


	// °Å¸®º¤ÅÍ
	POINT Dist_vec = { BulletLoc.x - location.x, BulletLoc.y - location.y };

	// ´ÜÀ§º¤ÅÍ ( ¹æÇâ )
	POINTF Unit_vec = { (float)Dist_vec.x / Distance, (float)Dist_vec.y / Distance };

	BulletBase* Bullet = new Bullet_Normal(BulletLoc, Unit_vec);
	Bullet->SetSize(BulletSize, BulletSize);
	result.Bullet = Bullet;


	if (RealDegree == 345) degree = 0;


	


	return result;
}

