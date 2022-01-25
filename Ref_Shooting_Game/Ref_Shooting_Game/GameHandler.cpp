#include "GameHandler.h"
#include "PlayerBase.h"
#include "enemyBase.h"
#include "Bullet_Normal.h"
#include <iostream>

GameHandler* GameHandler::Instance = nullptr;
HWND GameHandler::hWnd = NULL;

GameHandler::GameHandler()
{
	Bullet_SemaHnd = CreateSemaphore(NULL, 1, 1, NULL);
	Enemy_SemaHnd = CreateSemaphore(NULL, 1, 1, NULL);
	player = new PlayerBase();
	EnemyBase* enemy = new EnemyBase();
	CreateEnemy(enemy); //test

	CreateThread(NULL, 0, enemy_move, (LPVOID)enemy, 0, NULL);
	CreateThread(NULL, 0, enemy_attack, (LPVOID)enemy, 0, NULL);

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
		(*it)->DrawObject(hdc);
	}
	ReleaseSemaphore(Bullet_SemaHnd, 1, NULL);

	WaitForSingleObject(Enemy_SemaHnd, INFINITE);
	for (auto it = Enemys.begin(); it != Enemys.end(); it++)
	{
		(*it)->DrawObject(hdc);
	}
	ReleaseSemaphore(Enemy_SemaHnd, 1, NULL);

}


void GameHandler::OnKeyDown(WPARAM wParam)
{
	return;
	int player_x = player->GetLocation().x;
	int player_y = player->GetLocation().y;
	switch (wParam)
	{
	case 0x57:  // W
		player->SetLocation(POINT{ player_x,player_y - 10 });
		break;
	case 0x41:  // A
		player->SetLocation(POINT{ player_x-10,player_y});
		break;
	case 0x53:  // S
		player->SetLocation(POINT{ player_x,player_y + 10 });
		break;
	case 0x44:  // D
		player->SetLocation(POINT{ player_x+10,player_y});
		break;
	case 0x48:  // H
	{
		BulletBase* Bullet = player->Attack();
		Bullets.push_back(Bullet);
		CreateThread(NULL, 0, BulletTR, (LPVOID)Bullet, 0, NULL);
	}
		break;
	case 0x4A:
		break;
	default:
		break;
	}
}

GameHandler* GameHandler::GetInstance()
{
	if (Instance == nullptr)
		Instance = new GameHandler();
	
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
    GameHandler* play = GetInstance();
    PlayerBase* player = play->player;
    
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
            if (player->GetLocation().x >= 10)
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
            if (player->GetLocation().x <= 1020) // 여기다가 하면 됨
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
			CreateThread(NULL, 0, BulletTR, (LPVOID)Bullet, 0, NULL);
		}
		Sleep(100);
		
	}

	return 0;
}

DWORD WINAPI GameHandler::enemy_attack(LPVOID param) // 적의 공격 스레드(1초마다 공격합니다)
{
	GameHandler* play = GetInstance();
	EnemyBase * enemy = (EnemyBase*)param;;


	while (1)
	{
		WaitForSingleObject(play->Enemy_SemaHnd, INFINITE);		
		if (enemy == nullptr) {
			cout << "asdf" << endl;
			ReleaseSemaphore(play->Enemy_SemaHnd, 1, NULL);
			break;
		}
		//BulletBase* Bullet = enemy->Attack();
		//play->CreateBullet(Bullet);
		//CreateThread(NULL, 0, BulletTR, (LPVOID)Bullet, 0, NULL);
		ReleaseSemaphore(play->Enemy_SemaHnd, 1, NULL);
		Sleep(1000);	// 1초
	}

	return 0;
}

DWORD WINAPI GameHandler::enemy_move(LPVOID param) //적의 움직임을 담당하는 스레드입니다.
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

void GameHandler::DeleteBullet(BulletBase* DelBullet)
{
	
	if (DelBullet == nullptr) return; // null 값이면 리턴
	
	WaitForSingleObject(Bullet_SemaHnd, INFINITE);	
	for (auto it = Bullets.begin(); it != Bullets.end(); it++)
	{
		if (*it == DelBullet)
		{
			delete    DelBullet;
			it = Bullets.erase(it);
		   
			break;

		}
	}
	ReleaseSemaphore(Bullet_SemaHnd, 1, NULL);
}

void GameHandler::DeleteEnemy(EnemyBase* DelEnemy) 
{
	if (DelEnemy == nullptr) return; // null 값이면 리턴

	WaitForSingleObject(Bullet_SemaHnd, INFINITE);
	for (auto it = Enemys.begin(); it != Enemys.end(); it++)
	{
		if (*it == DelEnemy)
		{
			delete    DelEnemy;
			it = Enemys.erase(it);

			break;

		}
	}
	ReleaseSemaphore(Bullet_SemaHnd, 1, NULL);
}

//bullet 생성
void GameHandler::CreateBullet(BulletBase* newBullet)
{		
	
			WaitForSingleObject(Bullet_SemaHnd, INFINITE);
			Bullets.push_back(newBullet);
			ReleaseSemaphore(Bullet_SemaHnd, 1, NULL);

}

//Enemy 생성
void GameHandler::CreateEnemy(EnemyBase* newEnemy) {
	WaitForSingleObject(Enemy_SemaHnd, INFINITE);
	Enemys.push_back(newEnemy);
	ReleaseSemaphore(Enemy_SemaHnd, 1, NULL);
}

DWORD WINAPI GameHandler::BulletTR(LPVOID param)
{
	BulletBase* Bullet = (BulletBase*)param;
	if (Bullet != nullptr)
	{
		while (1)
		{

			bool result = Bullet->MoveNext();
			InvalidateRect(hWnd, NULL, false);

			if (result == false) 
			{
				GetInstance()->DeleteBullet(Bullet);
				break;
			}
			Sleep(10);
		}
		
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
