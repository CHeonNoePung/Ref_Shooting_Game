#pragma once
#include "framework.h"
#include <vector>
#include <map>


using namespace std;
class Entity;
class BulletBase;
class GameHandler
{
public:
	void OnPaint(HDC hdc, HINSTANCE hInst);
	void OnKeyDown(WPARAM wParam);

	static GameHandler* GetInstance();
	static void DestroyInstance();
	void InitBitmap(HINSTANCE hInst);

	//
	static DWORD WINAPI test(LPVOID param);
	static DWORD WINAPI attack(LPVOID param);
	static DWORD WINAPI enemy_attack(LPVOID param);
	static DWORD WINAPI enemy_move(LPVOID param);
	static DWORD WINAPI BulletTR(LPVOID param);
	static DWORD WINAPI StageTR(LPVOID param);

	void GameStart();
	void GameOver();
	void ResetGame();
	void RestartGame();
	bool EnemyCollisionTest(class EnemyBase* ColEnemy);

	int BulletCollisionTestToEnemy(BulletBase* ColBullet);
	bool BulletCollisionTestToPlayer(BulletBase* ColBullet);

	void DeleteBullet(int KeyCode);
	void DeleteEnemy(int KeyCode);
	void CreateBullet(BulletBase* newBullet);
	void CreateEnemy(EnemyBase* newEnemy);
	int GetPlayerLife();

	int S_Bit();

private:
	GameHandler();
	~GameHandler();
	static GameHandler* Instance;
	HINSTANCE hInst;
	HANDLE Bullet_SemaHnd;
	HANDLE Enemy_SemaHnd;

	map<int, class BulletBase*> Bullets;
	map<int, class EnemyBase*> Enemys;

	bool bGameover;
	int choose_num;
	bool TF;

	int StageKey;

	HBITMAP BIT_Frame;
	HBITMAP BIT_Heart;

	class PlayerBase* player;
	class PageStart* start;
	class PageEnd* end;
	class PlayerChoose* player_c;
};

