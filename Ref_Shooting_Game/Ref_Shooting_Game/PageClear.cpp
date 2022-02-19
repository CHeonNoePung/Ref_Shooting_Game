#include "PageClear.h"


PageClear::PageClear()
{
	end = 1;
}

void PageClear::DrawClear(HDC hdc)
{
	HDC hdc2 = CreateCompatibleDC(hdc);

	//HBITMAP MyBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_GAMEOVER));//��Ʈ�� ���ҽ��� �޾ƿ´�.
	//HBITMAP OldBitmap = (HBITMAP)SelectObject(hdc2, MyBitmap); //�޸�DC�� ��Ʈ�ʿ�����Ʈ�� �ִ´�.
//	BitBlt(hdc, 590, 100, 700, 200, hdc2, 0, 0, SRCCOPY); // DC�� ����(SRCCOPY)�Ѵ�.
	TransparentBlt(hdc, 580, 125, 236, 236, hdc2, 0, 0, 236, 236, RGB(255, 255, 255));

	WCHAR buf[100] = { 0, }; //���ڿ� ����
	int x = 640;
	int y = 400;

	Rectangle(hdc, 645, 405, 755, 500);
	if (end == 1)
	{

		Rectangle(hdc, 650, 415, 750, 440);

	}
	else if (end == 2)
	{
		Rectangle(hdc, 660, 440, 740, 465);

	}

	//wsprintfW(buf, L"RESTART");
	//TextOut(hdc, x + 30, y + 20, buf, lstrlenW(buf));
	wsprintfW(buf, L"GO TO START");
	TextOut(hdc, x + 15, y + 20, buf, lstrlenW(buf));
	wsprintfW(buf, L"EXIT GAME");
	TextOut(hdc, x + 25, y + 45, buf, lstrlenW(buf));
}

int PageClear::end_choose(WPARAM wParam)
{
	int x = 0;
	switch (wParam)
	{
	case 0x26:  // ����
		end--;
		if (end == 0)
			end = 3;
		break;
	case 0x28:  // �Ʒ���
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

