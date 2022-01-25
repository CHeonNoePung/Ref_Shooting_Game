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
	static DWORD WINAPI enemy_attack(LPVOID param);
	static DWORD WINAPI enemy_move(LPVOID param);
	void DeleteBullet(class BulletBase* DelBullet);
	void CreateBullet(BulletBase* newBullet);
	void DeleteEnemy(class EnemyBase* DelEnemy);
	void CreateEnemy(EnemyBase* newEnemy);
	//

	static DWORD WINAPI BulletTR(LPVOID param);
	static DWORD WINAPI EnemyTR(LPVOID param);
	
private:
	GameHandler();
	~GameHandler();
	static GameHandler* Instance;
	static HWND hWnd;
	HANDLE Bullet_SemaHnd;
	HANDLE Enemy_SemaHnd;

	list<class BulletBase*> Bullets;
	list<class EnemyBase*> Enemys;

	class PlayerBase* player;
};

