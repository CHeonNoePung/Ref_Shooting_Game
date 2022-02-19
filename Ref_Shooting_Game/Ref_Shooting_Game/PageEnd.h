#pragma once

#include "framework.h"
#include <iostream>
static int end;
class PageEnd
{
public: 
	PageEnd();
	static void SetGameOverBit(HBITMAP BITMAP);
	static void DeleteGameOverBit();
	void DrawEnd(HDC hdc);
	int end_choose(WPARAM wparam);

private:
	static HBITMAP BIT_GameOver;
};

