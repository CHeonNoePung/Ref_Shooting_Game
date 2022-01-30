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
	Object();
	virtual void DrawObject(HDC hdc);
	POINT GetLocation();
	void SetLocation(POINT point);
	void SetSize(int width, int height);
	RECT GetRect();
protected:
	POINT Location;
	int width;
	int height;

};

