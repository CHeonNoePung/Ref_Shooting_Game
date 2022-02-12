#include "BulletBase.h"
#include <iostream>

int BulletBase::g_KeyCode = 0;

BulletBase::BulletBase()
{
	Velocity = POINTF{0.0f, 0.0f};
	Location = POINT{ 0,0 };
	LocationF = POINTF{ 0,0 };
	KeyCode = g_KeyCode++;
	Speed = 1;

}

BulletBase::BulletBase(POINT newLocation, POINTF newVelocity)
{
	Location = newLocation;
	LocationF = { (float)newLocation.x,(float)newLocation.y };
	Velocity = newVelocity;
	KeyCode = g_KeyCode++;
	Speed = 1;

}

bool BulletBase::MoveNext()
{
	LocationF = { LocationF.x + Velocity.x * Speed, LocationF.y + Velocity.y * Speed };
	Location = {(LONG)LocationF.x , (LONG)LocationF.y };

	if (Location.y < 0) return false;
	// ȭ�� ũ�⸦ ���� ���ؼ� ���Ƿ� ��Ʈ�ʿ� ������ ��ǥ������ ������
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

void BulletBase::SetSpeed(int newSpeed)
{
	Speed = newSpeed;
}