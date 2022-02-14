#include "PlayerChoose.h"


PlayerChoose::PlayerChoose()
{
}

void PlayerChoose::DrawChoose(HDC  hdc)
{
	WCHAR buf[100] = { 0, };//버퍼 설정
	int a = 600;
	int b = 200;
	Rectangle(hdc, a, b, a + 90, b+100);
	Rectangle(hdc, a + 100, b, a + 190, b+100);
	//Rectangle(hdc, a+200, 100, a+290, 200);
	wsprintfW(buf, L"1.일반형");
	TextOut(hdc, a + 15, b+40, buf, lstrlenW(buf));
	wsprintfW(buf, L"2.관통형");
	TextOut(hdc, a + 115, b+40, buf, lstrlenW(buf));

}

int PlayerChoose::player_choose(WPARAM wParam)
{
	int p_c = 0;
	switch (wParam)
	{
	case 0x31:  // 1
		p_c = 1;
		break;
	case 0x32:  // 2
		p_c = 2;
		break;
	}
	return p_c;
}
