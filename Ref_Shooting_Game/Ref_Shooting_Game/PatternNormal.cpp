#include "PatternNormal.h"
#include "Bullet_Normal.h"

PatternNormal::PatternNormal(int Interval, int size) : PatternBase(Interval, size)
{
}

PatternResult PatternNormal::Next(RECT rect)
{
	PatternResult result;


	// 정중앙 위치 계산
	POINT location;
	location.x = rect.left + (rect.right - rect.left) / 2 - BulletSize / 2;
	location.y = rect.top + (rect.bottom - rect.top) / 2 - BulletSize / 2;

	BulletBase* Bullet = new Bullet_Normal(location, POINTF{ 0, 3 });		//GetLocation() 은 현재 위치 x,y 좌표값, POINTF 는 총알 속도 지정														//newLocation, newVelocity
	Bullet->SetSize(BulletSize, BulletSize);

	result.Bullet = Bullet;
	result.Interval = BulletInterval;

	return result;
}

