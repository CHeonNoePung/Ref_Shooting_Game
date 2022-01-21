#pragma once
#include "framework.h"
#include <vector>
#include <list>

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
	static DWORD WINAPI attack(LPVOID param);
	static DWORD WINAPI enomy_attack(LPVOID param);
	void DeleteBullet(class BulletBase* DelBullet);
	void CreateBullet(BulletBase* newBullet);
	//

	static DWORD WINAPI BulletTR(LPVOID param);
	
private:
	GameHandler();
	~GameHandler();
	static GameHandler* Instance;
	static HWND hWnd;
	HANDLE Bullet_SemaHnd;

	list<class BulletBase*> Bullets;


	class PlayerBase* player;
	class EnomyBase* enomy;
};

