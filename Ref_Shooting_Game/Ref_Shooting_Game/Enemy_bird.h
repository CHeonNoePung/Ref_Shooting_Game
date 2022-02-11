#pragma once

#include "EnemyBase.h"
#include <iostream>

class Enemy_bird
	: public EnemyBase
{
public:
	Enemy_bird();
	bool MoveNext();
	BulletBase* Attack();
	void DrawObject(HDC hdc);
	
private:

};

