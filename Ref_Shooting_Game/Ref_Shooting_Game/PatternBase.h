#pragma once

#include "windows.h"
class BulletBase;

struct PatternResult 
{
	BulletBase* Bullet;
	int Interval;
};


class PatternBase
{
public:
	PatternBase();
	PatternBase(int Interval, int size);

	// PatterResult를 반환 -> BulletBase와 다음 Bullet까지 몇초 기다려야되는지 알려줌 / 매개변수로 Player 좌표 필요
	virtual PatternResult Next(RECT rect) = 0;

	void SetBulletinterval(int newInterval);

	void SetBulletSize(int newSize);
protected:
	// 공격속도
	int BulletInterval;

	// Bullet크기
	int BulletSize;
};

