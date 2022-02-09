#include "GameHandler.h"
#include "PlayerBase.h"
#include "enemyBase.h"
#include "Bullet_Normal.h"
#include <iostream>

GameHandler* GameHandler::Instance = nullptr;
HWND GameHandler::hWnd = NULL;
HANDLE GameHandler::Instance_SemaHnd = NULL;

GameHandler::GameHandler()
{
	Bullet_SemaHnd = CreateSemaphore(NULL, 1, 1, NULL);
	Enemy_SemaHnd = CreateSemaphore(NULL, 1, 1, NULL);
	player = nullptr;
}

void GameHandler::GameStart()
{
	player = new PlayerBase();


	EnemyBase* enemy = new EnemyBase();
	enemy->SetSize(40, 40);
	CreateEnemy(enemy); //test
	

	EnemyBase* enemy2 = new EnemyBase(0, POINT{ 1000,100 });
	CreateEnemy(enemy2); // 윤석이가 테스트하려고 만져봄 / 스레드도 생성함
	

	EnemyBase* enemy3 = new EnemyBase(2, POINT{ 500,400 });
	CreateEnemy(enemy3); // 윤석이가 테스트하려고 만져봄
}

GameHandler::~GameHandler() 
{
	CloseHandle(Bullet_SemaHnd);
	CloseHandle(Enemy_SemaHnd);
}

void GameHandler::OnPaint(HDC hdc)
{	
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
    {   // 해당 키가 눌리면 0x8000을 반환함 해당 키들을 계속 확인하면서 키가 눌렸는지 확인함
        if (GetKeyState(0x57) & 0x8000) //w
        {
            if (player->GetLocation().y >= 10 )
            {
                player->SetLocation(POINT{ player->GetLocation().x, player->GetLocation().y - 10 });
                InvalidateRect(hWnd, NULL, FALSE);
            }
        }
        if (GetKeyState(0x41) & 0x8000) //a
        {
            if (player->GetLocation().x >= 400)
            {
                player->SetLocation(POINT{ player->GetLocation().x - 10, player->GetLocation().y });
                InvalidateRect(hWnd, NULL, FALSE);
            }
        }
        if (GetKeyState(0x53) & 0x8000) //s
        {
            if (player->GetLocation().y <= 1020) // 여기다가 하면 됨
            {
                player->SetLocation(POINT{ player->GetLocation().x, player->GetLocation().y + 10 });
                InvalidateRect(hWnd, NULL, FALSE);
            }
        }
        if (GetKeyState(0x44) & 0x8000) //d
        {
            if (player->GetLocation().x <= 1000) // 여기다가 하면 됨
            {
                player->SetLocation(POINT{ player->GetLocation().x + 10, player->GetLocation().y });
                InvalidateRect(hWnd, NULL, FALSE);
            }
        }
        Sleep(30);
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
		
		if (GetKeyState(0x48) & 0x8000) //d
		{
			BulletBase* Bullet = player->Attack();
			play->CreateBullet(Bullet);
		}
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
	EnemyBase* Enemy = Instance->Enemys.at(KeyCode);



	while (1)
	{
		WaitForSingleObject(Instance->Enemy_SemaHnd, INFINITE);	

		// 먼저 받았던 킷값을 가진 Enemy가 배열에 없으면 나감
		if (Instance->Enemys.count(KeyCode) < 1) 
		{
			ReleaseSemaphore(Instance->Enemy_SemaHnd, 1, NULL);
			break;
		}

		// Enemy가 가진 Bullet을 반환함
		BulletBase* Bullet = Enemy->Attack();
		Instance->CreateBullet(Bullet);

		ReleaseSemaphore(Instance->Enemy_SemaHnd, 1, NULL);
		Sleep(1000);	// 1초
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
	EnemyBase* Enemy = Instance->Enemys.at(KeyCode);				

	// 플레이어 받아옴
	PlayerBase* player = GetInstance()->player;						

	while (1)
	{
		WaitForSingleObject(Instance->Enemy_SemaHnd, INFINITE);	


		// 먼저 받았던 킷값을 가진 Enemy가 배열에 없으면 나감
		if (Instance->Enemys.count(KeyCode) < 1)					
		{
			ReleaseSemaphore(Instance->Enemy_SemaHnd, 1, NULL);
			break;
		}


		// Enemy를 다음 방향으로 이동시킴 / 맵밖에 나가면 false 반환
		bool result = Enemy->MoveNext();							
		InvalidateRect(hWnd, NULL, false);

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
			player->GetDamages(5);									
			ReleaseSemaphore(Instance->Enemy_SemaHnd, 1, NULL);
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
	Bullets.insert(make_pair(newBullet->GetKeyCode(),newBullet));		

	ReleaseSemaphore(Bullet_SemaHnd, 1, NULL);

	CreateThread(NULL, 0, BulletTR, &KeyCode, 0, NULL);
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
bool GameHandler::EnemyCollisionTest(EnemyBase* ColEnemy) {
	RECT HitBox;
	RECT EnemyRect = ColEnemy->GetRect();
	RECT PlayerRect = player->GetRect();
	if (IntersectRect(&HitBox, &EnemyRect, &PlayerRect))
		return true;
	else
		return false;
}

Entity* GameHandler::BulletCollisionTest(BulletBase* ColBullet) {
	if (ColBullet->IsPlayer()) 
	{
		EnemyBase* enemytest = nullptr;
		WaitForSingleObject(Enemy_SemaHnd, INFINITE);
		for (auto it = Enemys.begin(); it != Enemys.end(); it++)
		{
			RECT HitBox;
			RECT EnemyRect = (*it).second->GetRect();
			RECT BulletRect = ColBullet->GetRect();
			(*it).second->GetLocation();
			if (IntersectRect(&HitBox, &EnemyRect, &BulletRect))
			{
				
				enemytest = (*it).second;
				break;
			}
		}
		ReleaseSemaphore(Enemy_SemaHnd, 1, NULL);
		return enemytest;
	}
	else
	{
		RECT HitBox;
		RECT PlayerRect = player->GetRect();
		RECT BulletRect = ColBullet->GetRect();
		if (IntersectRect(&HitBox, &PlayerRect, &BulletRect))
		{
			return player;
		}
	}
	
	return nullptr;
}

//
DWORD WINAPI GameHandler::BulletTR(LPVOID param)
{
	return 0;
	GameHandler* Instance = GetInstance();


	// Bullet 가진 고유한 킷값을 매개변수로 받음
	int KeyCode = (int)(__int64)param;

	// 킷값을 이용하여 Bullet를 얻음
	BulletBase* Bullet = Instance->Bullets.at(KeyCode);

	while (1)
	{

		bool result = Bullet->MoveNext();
		InvalidateRect(hWnd, NULL, false);

			if (result == false) 
			{
				//GetInstance()->DeleteBullet(Bullet);
				break;
			}
			Entity* entity;
			entity = GetInstance()->BulletCollisionTest(Bullet);
			if (entity == nullptr) {
				
			}
			else if (entity->IsPlayer())
			{
				entity->GetDamages(1);
				break;
			}
			else
			{
				bool bDead = entity->GetDamages(1);
				if (bDead == true) {
					
					GetInstance()->DeleteEnemy((EnemyBase*)entity);
				}
				break;
			}
			Sleep(10);
		}
		GetInstance()->DeleteBullet(Bullet);
	}
	
	return 0;
}

DWORD WINAPI GameHandler::EnemyTR(LPVOID param) 
{
	EnemyBase* Enemy = (EnemyBase*)param;
	if (Enemy != nullptr)
	{
		while (1)
		{

			bool result = Enemy->MoveNext();
			InvalidateRect(hWnd, NULL, false);

			if (result == false)
			{
				GetInstance()->DeleteEnemy(Enemy);
				break;
			}
			Sleep(10);
		}

	}

	return 0;
}
