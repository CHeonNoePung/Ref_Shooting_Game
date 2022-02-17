#pragma once

#include "framework.h"
#include <iostream>
static int end;
class PageEnd
{
public: 
	PageEnd();
	void DrawEnd(HDC hdc, HINSTANCE hInst);
	int end_choose(WPARAM wparam);

private:
	
};

