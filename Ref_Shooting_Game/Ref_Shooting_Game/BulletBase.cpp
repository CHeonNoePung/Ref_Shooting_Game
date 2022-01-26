#include "BulletBase.h"
#include <iostream>

int BulletBase::g_KeyCode = 0;

BulletBase::BulletBase()
{
	Velocity = POINTF{0.0f, 0.0f};
	Location = POINT{ 0,0 };
	KeyCode = g_KeyCode++;
}

BulletBase::BulletBase(POINT newLocation, POINTF newVelocity)
{
	Location = newLocation;
	Velocity = newVelocity;
	KeyCode = g_KeyCode++;
}

bool BulletBase::MoveNext()
{
	Location = POINT{ Location.x + long(Velocity.x), Location.y + long(Velocity.y)};

	if (Location.y < 0) return false;
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
