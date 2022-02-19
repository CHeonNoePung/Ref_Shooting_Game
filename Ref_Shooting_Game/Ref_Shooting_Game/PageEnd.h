#pragma once

#include "framework.h"
#include <iostream>

class PageEnd
{
public: 
	PageEnd();
	void DrawEnd(HDC hdc, HINSTANCE hInst);
	int end_choose(WPARAM wparam);

private:
	int end;
};

