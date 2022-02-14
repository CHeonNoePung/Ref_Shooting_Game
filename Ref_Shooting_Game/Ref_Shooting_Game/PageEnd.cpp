#include "PageEnd.h"

PageEnd::PageEnd()
{
	end = 1;
}

void PageEnd::DrawEnd(HDC hdc)
{
	WCHAR buf[100] = { 0, }; //문자열 버퍼
	int x = 500;
	int y = 200;

	Rectangle(hdc, 500, 200, 650, 300);
	if (end == 1)
	{
		
		Rectangle(hdc, 550, 200, 600, 220);

	}
	else if (end == 2)
	{
		Rectangle(hdc, 550, 220, 600, 240);
	
	}
	
	else if (end == 3)
	{
		Rectangle(hdc, 550, 240, 700, 260);
		
	}

	wsprintfW(buf, L"다시 시작");
	TextOut(hdc, x + 15, y + 20, buf, lstrlenW(buf));
	wsprintfW(buf, L"시작 화면으로 이동");
	TextOut(hdc, x + 15, y + 40, buf, lstrlenW(buf));
	wsprintfW(buf, L"종료");
	TextOut(hdc, x + 15, y + 60, buf, lstrlenW(buf));
	
}

int PageEnd::end_choose(WPARAM wParam)
{
	int x = 0;
	switch (wParam)
	{
	case 0x26:  // 위쪽
		end--;
		if (end == 0)
			end = 3;
		break;
	case 0x28:  // 아래쪽
		end++;
		if (end == 4)
			end = 1;
		break;
	case 0x0D:// Enter
		x = end;
		break;
	}
	return x;
}

