#pragma once
#include "framework.h"

struct POINTF
{
	float x;
	float y;
};
class Object
{
public:
	virtual void DrawObject(HDC hdc);
	POINT GetLocation();
	void SetLocation(POINT point);
protected:
	POINT Location;
};

