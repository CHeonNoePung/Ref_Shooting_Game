#pragma warning(disable:4828)
#include "PatternRain.h"
#include "Bullet_Normal.h"
#include <math.h>
#include <iostream>
PatternRain::PatternRain(int Interval, int size) : PatternBase(Interval, size)
{
	num = 0;
}

PatternResult PatternRain::Next(PatternParam Param)
{
	PatternResult result;

	RECT rect = Param.EntityRect;
	RECT playerRect = Param.PlayerRect;
	// 정중앙 위치 계산
	POINT location;

	location.x = 700;
	location.y = 50;
	int BulletStopTime = 0;
	if (num % 2 == 0)
	{
		location.x -= 200 ;
		location.y += 50 * num;
		BulletStopTime = 500 + (4 - num/2) * BulletInterval;
		result.Interval = 0;
	}
	else
	{
		location.x += 200;
		location.y += 50 * (num-1);
		BulletStopTime = 500 + (4 - num/2) * BulletInterval;
		result.Interval = BulletInterval;
	}
	std::cout << BulletStopTime << std::endl;
	num++;


	BulletBase* Bullet;

	POINT Dist_vec = { playerRect.left - location.x, playerRect.top - location.y };	// 거리벡터 구함
	int Distance = (int)sqrt(pow(Dist_vec.x, 2) + pow(Dist_vec.y, 2));				// 거리구함

	POINTF Unit_vec;
	Unit_vec.x = (float)Dist_vec.x / Distance;									// 단위벡터로 변환
	Unit_vec.y = (float)Dist_vec.y / Distance;

	Bullet = new Bullet_Normal(location, Unit_vec, 1);


	Bullet->SetSize(BulletSize, BulletSize);
	Bullet->StopMoving(BulletStopTime);

	result.Bullet = Bullet;


	if (num >= 10) num = 0;

	return result;
}

