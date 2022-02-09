#pragma once
#include "framework.h"
#include <vector>
#include <map>

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

	void GameStart();
	bool EnemyCollisionTest(class EnemyBase* ColEnemy);
	EnemyBase* BulletCollisionTest(class BulletBase* ColBullet);
	void DeleteBullet(int KeyCode);
	void DeleteEnemy(int KeyCode);
	void CreateBullet(BulletBase* newBullet);
	void CreateEnemy(EnemyBase* newEnemy);
	//

	static DWORD WINAPI BulletTR(LPVOID param);

	
private:
	GameHandler();
	~GameHandler();
	static GameHandler* Instance;
	static HWND hWnd;
	static HANDLE Instance_SemaHnd;
	HANDLE Bullet_SemaHnd;
	HANDLE Enemy_SemaHnd;

	map<int,class BulletBase*> Bullets;			// 자료구조 map 검색
	map<int,class EnemyBase*> Enemys;

	class PlayerBase* player;
};

