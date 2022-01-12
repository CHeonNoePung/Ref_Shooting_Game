#pragma once
#include "framework.h"
#include <vector>

using namespace std;
class GameHandler
{
public:
	void OnPaint(HDC hdc);
	void OnKeyDown(WPARAM wParam);

	static GameHandler* GetInstance();
	static void DestroyInstance();
	static void SethWnd(HWND hWnd);
	
	//
	static DWORD WINAPI test(LPVOID param);
	//

	static DWORD WINAPI BulletTR(LPVOID param);
	
private:
	GameHandler();
	~GameHandler() {};
	static GameHandler* Instance;
	static HWND hWnd;

	vector<class BulletBase*> Bullets;


	class PlayerBase* player;
};

