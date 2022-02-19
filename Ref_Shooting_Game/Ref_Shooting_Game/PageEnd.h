#pragma once

#include "framework.h"
#include <iostream>

class PageEnd
{
public: 
	PageEnd();
	static void SetGameOverBit(HBITMAP BITMAP);
	static void DeleteGameOverBit();
	void DrawEnd(HDC hdc, HINSTANCE hInst);
	int end_choose(WPARAM wparam);

private:
	int end;
	static HBITMAP BIT_GameOver;
};

