#include "BulletBase.h"
#include <iostream>

int BulletBase::g_KeyCode = 0;

BulletBase::BulletBase()
{
	Velocity = POINTF{0.0f, 0.0f};
	Location = POINT{ 0,0 };
	LocationF = POINTF{ 0,0 };
	KeyCode = g_KeyCode++;

}

BulletBase::BulletBase(POINT newLocation, POINTF newVelocity)
{
	Location = newLocation;
	LocationF = { (float)newLocation.x,(float)newLocation.y };
	Velocity = newVelocity;
	KeyCode = g_KeyCode++;

}

bool BulletBase::MoveNext()
{
	LocationF = { LocationF.x + Velocity.x, LocationF.y + Velocity.y };
	Location = {(LONG)LocationF.x, (LONG)LocationF.y};

	if (Location.y < 0) return false;
	// 화면 크기를 설정 안해서 임의로 비트맵에 설정된 좌표값으로 설정함
	else if (Location.y > 690) return false;
	else return true;
}

void BulletBase::SetVelocity(POINTF pointf)
{
	Velocity = pointf;
}

POINTF BulletBase::GetVelocity()
{
	return Velocity;
}

int BulletBase::GetKeyCode()
{
	return KeyCode;
}
