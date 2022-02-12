#pragma once

#include "windows.h"
class BulletBase;

struct PatternResult 
{
	BulletBase* Bullet;
	int Interval;
};

struct PatternParam
{
	RECT EntityRect;
	RECT PlayerRect;
};


class PatternBase
{
public:
	PatternBase();
	PatternBase(int Interval, int size);

	// PatterResult�� ��ȯ -> BulletBase�� ���� Bullet���� ���� ��ٷ��ߵǴ��� �˷��� / �Ű������� Player ��ǥ �ʿ�
	virtual PatternResult Next(PatternParam Param) = 0;

	void SetBulletinterval(int newInterval);

	void SetBulletSize(int newSize);
protected:
	// ���ݼӵ�
	int BulletInterval;

	// Bulletũ��
	int BulletSize;
};

