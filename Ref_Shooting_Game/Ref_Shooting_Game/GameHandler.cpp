#include "GameHandler.h"
#include "PlayerBase.h"
#include "enemyBase.h"
#include "Bullet_Normal.h"
#include "PlayerChoose.h"
#include "PageStart.h"
#include "PageEnd.h"
#include "Stage.h"
#include <iostream>

GameHandler* GameHandler::Instance = nullptr;
HWND GameHandler::hWnd = NULL;
HANDLE GameHandler::Instance_SemaHnd = NULL;

GameHandler::GameHandler()
{
	Bullet_SemaHnd = CreateSemaphore(NULL, 1, 1, NULL);
	Enemy_SemaHnd = CreateSemaphore(NULL, 1, 1, NULL);
	//player = nullptr;

	start_num = 0;
	StageKey = 0;
	bGameover = false;
	choose_num = 0;
	TF = false;

	start = new PageStart();
	end = new PageEnd();
	player_c = new  PlayerChoose();
	player = new  PlayerBase();

}

void GameHandler::GameStart()
{
	StageKey++;
	if (choose_num == 0)
		return;

	CreateThread(NULL, 0, GameHandler::StageTR, (LPVOID)(__int64)StageKey, 0, NULL);

	CreateThread(NULL, 0, GameHandler::test, (LPVOID)NULL, 0, NULL);            // 플레이어 이동 스레드
	CreateThread(NULL, 0, GameHandler::attack, (LPVOID)NULL, 0, NULL);			// 플레이어 공격 스레드

}

void GameHandler::GameOver()
{
	bGameover = true;
}
void GameHandler::ResetGame()
{
	start_num = 0;
	bGameover = false;
	TF = false;
	choose_num = 0;
	player->Reset();
}
void GameHandler::RestartGame()
{
	TF = false;
	bGameover = false;
	player->Reset();
	GameStart();
}
GameHandler::~GameHandler()
{
	delete player;

	delete start;
	delete end;
	delete player_c;
	delete player;

	CloseHandle(Bullet_SemaHnd);
	CloseHandle(Enemy_SemaHnd);
}

void GameHandler::OnPaint(HDC hdc)
{

	if (start_num != 3) {
		start->DrawStart(hdc);
		return;
	}
	else if (!choose_num) {
		player_c->DrawChoose(hdc);
		return;
	}

	if (bGameover == true)
	{
		end->DrawEnd(hdc);
		return;
	}

	player->DrawObject(hdc);
	WaitForSingleObject(Bullet_SemaHnd, INFINITE);
	for (auto it = Bullets.begin(); it != Bullets.end(); it++)
	{
		(*it).second->DrawObject(hdc);
	}
	ReleaseSemaphore(Bullet_SemaHnd, 1, NULL);

	WaitForSingleObject(Enemy_SemaHnd, INFINITE);
	for (auto it = Enemys.begin(); it != Enemys.end(); it++)
	{
		(*it).second->DrawObject(hdc);
	}
	ReleaseSemaphore(Enemy_SemaHnd, 1, NULL);

}

void GameHandler::OnKeyDown(WPARAM wParam)
{

	if (start_num != 3) {		//
		start_num = start->start_choose(wParam);
		if (start_num == 4)
			ExitProcess(0);
	}
	else if (choose_num == 0) {
		choose_num = player_c->player_choose(wParam);
		if (choose_num != 0) GameStart();
	}

	if (bGameover == true)
	{
		int x;
		x = end->end_choose(wParam);

		// 1이 게임 재시작, 2: 시작 화면 이동, 3: 게임 종료
		if (x == 1)
		{
			Sleep(300);		// 모든 스레드가 죽기를 기다림
			RestartGame();
		}
		else if (x == 2)
		{
			ResetGame();
		}
		else if (x == 3)
		{
			ExitProcess(0);
		}
	}
	return;

}

GameHandler* GameHandler::GetInstance()
{
	if (Instance == nullptr)
	{
		Instance = new GameHandler();
	}

	return Instance;
}
void GameHandler::DestroyInstance()
{
	if (Instance)
	{
		delete Instance;
	}
}

void GameHandler::SethWnd(HWND nhWnd)
{
	hWnd = nhWnd;
}

// 움직이는거 쓰레드로 구현
DWORD __stdcall GameHandler::test(LPVOID param)
{

	GameHandler* Instance = GetInstance();
	PlayerBase* player = Instance->player;



	while (1)
	{
		if (Instance->bGameover == true) break;
		if (player->IsDead()) continue;
		if (Instance->TF == true && Instance->choose_num == 2) { continue; }
		// 해당 키가 눌리면 0x8000을 반환함 해당 키들을 계속 확인하면서 키가 눌렸는지 확인함
		if (GetKeyState(0x57) & 0x8000) //w
		{
			if (player->GetLocation().y >= 14)
			{
				player->SetLocation(POINT{ player->GetLocation().x, player->GetLocation().y - 5 });
			}
		}
		if (GetKeyState(0x41) & 0x8000) //a
		{
			if (player->GetLocation().x >= 401)
			{
				player->SetLocation(POINT{ player->GetLocation().x - 5, player->GetLocation().y });
			}
		}
		if (GetKeyState(0x53) & 0x8000) //s
		{
			if (player->GetLocation().y <= 665) // 여기다가 하면 됨
			{
				player->SetLocation(POINT{ player->GetLocation().x, player->GetLocation().y + 5 });
			}
		}
		if (GetKeyState(0x44) & 0x8000) //d
		{
			if (player->GetLocation().x <= 970) // 여기다가 하면 됨
			{
				player->SetLocation(POINT{ player->GetLocation().x + 5, player->GetLocation().y });
			}
		}
		Sleep(15);
		//https://mlpworld.tistory.com/entry/키보드-상태-조사
	}

	return 0;
}

DWORD WINAPI GameHandler::attack(LPVOID param)
{
	GameHandler* play = GetInstance();
	PlayerBase* player = play->player;

	while (1)
	{
		if (Instance->bGameover == true) break;
		if (player->IsDead()) continue;

		if (GetKeyState(0x48) & 0x8000) //d
		{
			if (play->TF == true && play->choose_num == 2) { continue; }
			BulletBase* Bullet = player->Attack(play->choose_num).Bullet;
			play->CreateBullet(Bullet);
			play->TF = true;
		}
		else play->TF = false;
		Sleep(100);

	}

	return 0;
}

DWORD WINAPI GameHandler::enemy_attack(LPVOID param) // 적의 공격 스레드(1초마다 공격합니다)
{
	GameHandler* Instance = GetInstance();


	// Enemy가 가진 고유한 킷값을 매개변수로 받음
	int KeyCode = (int)(__int64)param;

	// 킷값을 이용하여 Enemy를 얻음
	EnemyBase* Enemy = nullptr;



	while (1)
	{
		if (Instance->bGameover == true) break;
		WaitForSingleObject(Instance->Enemy_SemaHnd, INFINITE);

		// 먼저 받았던 킷값을 가진 Enemy가 배열에 없으면 나감
		if (Instance->Enemys.count(KeyCode) < 1)
		{
			ReleaseSemaphore(Instance->Enemy_SemaHnd, 1, NULL);
			break;
		}

		if (Enemy == nullptr) Enemy = Instance->Enemys.at(KeyCode);

		// Enemy가 가진 패턴을 반환함
		PatternParam Param;
		Param.EntityRect = Enemy->GetRect();
		Param.PlayerRect = Instance->player->GetRect();

		PatternResult result = Enemy->Attack(Param);

		BulletBase* Bullet = result.Bullet;
		int Interval = result.Interval;
		Instance->CreateBullet(Bullet);

		ReleaseSemaphore(Instance->Enemy_SemaHnd, 1, NULL);
		Sleep(Interval);
	}
	return 0;
}


//적의 움직임을 담당하는 스레드
DWORD WINAPI GameHandler::enemy_move(LPVOID param)
{
	GameHandler* Instance = GetInstance();


	// Enemy가 가진 고유한 킷값을 매개변수로 받음
	int KeyCode = (int)(__int64)param;

	// 킷값을 이용하여 Enemy를 얻음
	EnemyBase* Enemy = nullptr;

	// 플레이어 받아옴
	PlayerBase* player = GetInstance()->player;

	while (1)
	{
		if (Instance->bGameover == true) break;
		WaitForSingleObject(Instance->Enemy_SemaHnd, INFINITE);


		// 먼저 받았던 킷값을 가진 Enemy가 배열에 없으면 나감
		if (Instance->Enemys.count(KeyCode) < 1)
		{
			ReleaseSemaphore(Instance->Enemy_SemaHnd, 1, NULL);
			break;
		}

		if (Enemy == nullptr) Enemy = Instance->Enemys.at(KeyCode);

		// Enemy를 다음 방향으로 이동시킴 / 맵밖에 나가면 false 반환
		bool result = Enemy->MoveNext();

		// false(맵밖 나가면) 스레드 종료
		if (result == false)
		{
			ReleaseSemaphore(Instance->Enemy_SemaHnd, 1, NULL);
			break;
		}


		// 플레이어와 부딪혔는지 검사 / 부딪히면 true 반환
		bool hitresult = GetInstance()->EnemyCollisionTest(Enemy);

		// true(부딪히면) 플레이어 5데미지 입히고 스레드 종료
		if (hitresult == true)
		{
			bool bLifeZero = player->GetDamages(5);
			ReleaseSemaphore(Instance->Enemy_SemaHnd, 1, NULL);

			if (bLifeZero == true) Instance->GameOver();
			break;
		}
		ReleaseSemaphore(Instance->Enemy_SemaHnd, 1, NULL);

		Sleep(80);

	}

	Instance->DeleteEnemy(KeyCode);


	return 0;
}

void GameHandler::DeleteBullet(int KeyCode)
{
	WaitForSingleObject(Bullet_SemaHnd, INFINITE);

	// 해당 키코드가 존재할 경우에만 제거
	if (Instance->Bullets.count(KeyCode) > 0)
	{
		delete Bullets.at(KeyCode);
		Bullets.erase(KeyCode);
	}

	ReleaseSemaphore(Bullet_SemaHnd, 1, NULL);
}

void GameHandler::DeleteEnemy(int KeyCode)
{
	WaitForSingleObject(Enemy_SemaHnd, INFINITE);

	// 해당 키코드가 존재할 경우에만 제거
	if (Instance->Enemys.count(KeyCode) > 0)
	{
		delete Enemys.at(KeyCode);
		Enemys.erase(KeyCode);
	}

	ReleaseSemaphore(Enemy_SemaHnd, 1, NULL);
}

//bullet 생성
void GameHandler::CreateBullet(BulletBase* newBullet)
{
	int KeyCode = newBullet->GetKeyCode();
	WaitForSingleObject(Bullet_SemaHnd, INFINITE);

	// 생성된 Bullet을 배열로 관리하기 위해 map자료구조로 이뤄진 Bullets에 추가
	Bullets.insert(make_pair(KeyCode, newBullet));

	ReleaseSemaphore(Bullet_SemaHnd, 1, NULL);

	CreateThread(NULL, 0, BulletTR, (LPVOID)(__int64)KeyCode, 0, NULL);
}

//Enemy 생성
void GameHandler::CreateEnemy(EnemyBase* newEnemy)
{
	int KeyCode = newEnemy->GetKeyCode();
	WaitForSingleObject(Enemy_SemaHnd, INFINITE);

	// 생성된 Enemy를 배열로 관리하기 위해 map자료구조로 이뤄진 Enemys에 추가
	Enemys.insert(make_pair(KeyCode, newEnemy));

	ReleaseSemaphore(Enemy_SemaHnd, 1, NULL);

	CreateThread(NULL, 0, enemy_move, (LPVOID)(__int64)KeyCode, 0, NULL);
	CreateThread(NULL, 0, enemy_attack, (LPVOID)(__int64)KeyCode, 0, NULL);
}



//충돌판정
bool GameHandler::EnemyCollisionTest(EnemyBase* ColEnemy)
{

	if (player->IsDead()) return false;
	RECT HitBox;
	RECT EnemyRect = ColEnemy->GetRect();
	RECT PlayerRect = player->GetRect();
	if (IntersectRect(&HitBox, &EnemyRect, &PlayerRect))
		return true;
	else
		return false;
}

int GameHandler::BulletCollisionTestToEnemy(BulletBase* ColBullet)
{

	int resultKey = -1;
	WaitForSingleObject(Enemy_SemaHnd, INFINITE);
	for (auto it = Enemys.begin(); it != Enemys.end(); it++)
	{
		RECT HitBox;
		RECT EnemyRect = (*it).second->GetRect();
		RECT BulletRect = ColBullet->GetRect();
		(*it).second->GetLocation();
		if (IntersectRect(&HitBox, &EnemyRect, &BulletRect))
		{

			resultKey = (*it).second->GetKeyCode();
			break;
		}
	}
	ReleaseSemaphore(Enemy_SemaHnd, 1, NULL);

	return resultKey;
}
bool GameHandler::BulletCollisionTestToPlayer(BulletBase* ColBullet)
{
	if (player->IsDead()) return false;
	RECT HitBox;
	RECT PlayerRect = player->GetRect();
	RECT BulletRect = ColBullet->GetRect();
	if (IntersectRect(&HitBox, &PlayerRect, &BulletRect))
	{
		return true;
	}

	return false;
}


//
DWORD WINAPI GameHandler::BulletTR(LPVOID param)
{

	GameHandler* Instance = GetInstance();


	// Bullet 가진 고유한 킷값을 매개변수로 받음
	int KeyCode = (int)(__int64)param;

	// 킷값을 이용하여 Bullet를 얻음
	BulletBase* Bullet = Instance->Bullets.at(KeyCode);

	while (1)
	{
		if (Instance->bGameover == true) break;


		bool result = Bullet->MoveNext();


		if (result == false) break;


		// Bullet이 플레이어 소유일경우
		if (Bullet->IsPlayer())
		{

			if (Instance->choose_num == 2)
			{
				if (Instance->TF == false || Instance->player->IsDead() == true) break;
			}


			// 모든 Enemy에 대해서 충돌검사를 한 뒤, 충돌난 Enemy의 KeyCode 반환 / 없을경우 -1 반환
			int colKeyCode = Instance->BulletCollisionTestToEnemy(Bullet);
			if (colKeyCode != -1)
			{
				WaitForSingleObject(Instance->Enemy_SemaHnd, INFINITE);

				EnemyBase* Enemy = nullptr;
				bool bDead = false;

				// 해당 키코드가 Enemys에 존재하는지 검사
				if (Instance->Enemys.count(colKeyCode) > 0)
				{
					// 키코드에 해당하는 Enemy를 가져옴
					Enemy = Instance->Enemys.at(colKeyCode);

					// 1데미지를 준 뒤, 죽었으면 true  아니면 false 반환

					if (Instance->choose_num == 2)
						bDead = Enemy->GetDamages(5);
					else
						bDead = Enemy->GetDamages(1);
				}

				ReleaseSemaphore(Instance->Enemy_SemaHnd, 1, NULL);

				// Enemy가 죽었을경우 Delete함		/      위 코드와 분리한 이유는 Delete 안에도 세마포가 있어서 중복이됨
				if (bDead == true)
				{
					Instance->DeleteEnemy(colKeyCode);
				}
				if (Instance->choose_num != 2)
					break;
			}

		}

		else  // Bullet이 플레이어 소유가 아닐경우
		{
			// 플레이어와 충돌검사를 한 뒤, 충돌시 true 아니면 false 반환
			bool colResult = Instance->BulletCollisionTestToPlayer(Bullet);
			if (colResult == true)
			{
				bool ck;
				ck = Instance->player->GetDamages(1);

				if (ck == true)
				{
					Instance->GameOver();
				}
				break;
			}
		}
		Sleep(10);
	}
	Instance->DeleteBullet(KeyCode);
	return 0;
}

DWORD WINAPI GameHandler::StageTR(LPVOID param)
{
	int Key = (int)(__int64)param;

	Stage* stage = new Stage();

	while (1)
	{
		if (Instance->bGameover == true || Instance->StageKey != Key) break;			// 게임이 종료 OR 현재 진행중인 스테이지와 다르면 종료
		EnemyBase* Enemy = stage->getMonsterBase();										// Sleep이 호출됨
		if (Instance->bGameover == true || Instance->StageKey != Key) break;			// Sleep중 게임이 종료될 수 있기때문에 한번더 검사함

		if (Enemy != nullptr)
		{
			GameHandler::GetInstance()->CreateEnemy(Enemy);
		}
		else
		{
			break;
		}

	}
	delete stage;
	return 0;
}


int GameHandler::S_Bit()
{
	return start_num;
}
