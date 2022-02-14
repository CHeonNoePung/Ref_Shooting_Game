#include "PageStart.h"

PageStart::PageStart()
{
	num = 1;
}
void PageStart::DrawStart(HDC hdc)
{

	WCHAR buf[100] = { 0, };//버퍼 설정
	int menu_x = 500;
	int menu_y = 200;
	if (num == 1) {
		wsprintfW(buf, L"▶                                            ◀");
		TextOut(hdc, menu_x - 25, menu_y + 40, buf, lstrlenW(buf));
	}
	else if(num == 2){
		wsprintfW(buf, L"▶                                            ◀");
		TextOut(hdc, menu_x - 25, menu_y + 80, buf, lstrlenW(buf));
	}
	Rectangle(hdc, menu_x , menu_y+30, menu_x + 160, menu_y + 65);
	Rectangle(hdc, menu_x, menu_y+70, menu_x + 160, menu_y + 105);

	wsprintfW(buf, L"1.시작");
	TextOut(hdc, menu_x + 15, menu_y + 40, buf, lstrlenW(buf));
	wsprintfW(buf, L"2.종료");
	TextOut(hdc, menu_x + 15, menu_y + 80, buf, lstrlenW(buf));
}


int PageStart::start_choose(WPARAM wParam)
{

	switch (wParam)
	{
	case 0x26:  // 위쪽
		if (num == 1)
			num = 2;
		else num = 1;
		break;
	case 0x28:  // 아래쪽
		if (num == 1)
			num = 2;
		else num = 1;
		break;
	case 0x0D:// Enter
		if(num==1)
		num = 3;
		if (num == 2)
			num = 4;
		break;
	}
	return num;
}