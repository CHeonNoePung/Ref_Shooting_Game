#pragma once
#include "framework.h"

struct POINTF
{
	float x;
	float y;
};

static int choose_num;
static int start_num;


class Object
{
public:
	Object();
	virtual void DrawObject(HDC hdc);
	POINT GetLocation();
	void SetLocation(POINT point);
	void SetSize(int width, int height);
	POINT GetSize();
	RECT GetRect();
	RECT GetRect_a();
	bool IsPlayer();
	void SetPlayer();
protected:
	POINT Location;
	int width;
	int height;
	bool bPlayer;
};

