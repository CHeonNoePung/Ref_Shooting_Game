#include "GameHandler.h"
#include "PlayerBase.h"
#include "Bullet_Normal.h"
#include <iostream>

GameHandler* GameHandler::Instance = nullptr;
HWND GameHandler::hWnd = NULL;

GameHandler::GameHandler()
{
    Bullet_SemaHnd = CreateSemaphore(NULL, 1, 1, NULL);
    player = new PlayerBase();
}

GameHandler::~GameHandler() 
{
    CloseHandle(Bullet_SemaHnd);
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
    case 0x48:
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




DWORD __stdcall GameHandler::test(LPVOID param)
{
    GameHandler* play = GetInstance();
    PlayerBase* player = play->player;

    while (1)
    {   
        if (GetKeyState(0x57) & 0x8000) //w
        {
            if (player->GetLocation().y >= 3 )
            {
                player->SetLocation(POINT{ player->GetLocation().x, player->GetLocation().y - 3 });
                InvalidateRect(hWnd, NULL, FALSE);
            }
        }
        if (GetKeyState(0x41) & 0x8000) //a
        {
            if (player->GetLocation().x >= 3)
            {
                player->SetLocation(POINT{ player->GetLocation().x - 3, player->GetLocation().y });
                InvalidateRect(hWnd, NULL, FALSE);
            }
        }
        if (GetKeyState(0x53) & 0x8000) //s
        {
            if (player->GetLocation().y <= 900) // ����ٰ� �ϸ� ��
            {
                player->SetLocation(POINT{ player->GetLocation().x, player->GetLocation().y + 3 });
                InvalidateRect(hWnd, NULL, FALSE);
            }
        }
        if (GetKeyState(0x44) & 0x8000) //d
        {
            if (player->GetLocation().x <= 1080) // ����ٰ� �ϸ� ��
            {
                player->SetLocation(POINT{ player->GetLocation().x + 3, player->GetLocation().y });
                InvalidateRect(hWnd, NULL, FALSE);
            }
        }
        Sleep(20);
        //https://mlpworld.tistory.com/entry/Ű����-����-����
    }

    return 0;
}

DWORD WINAPI GameHandler::attack(LPVOID param)
{
    GameHandler* play = GetInstance();
    PlayerBase* player = play->player;

    while (1)
    {   
        //GetKeyState: ���� ���� �����ִ��� Ȯ���ϴ� �Լ�
        if (GetKeyState(0x48) & 0x8000) //d
        {
            BulletBase* Bullet = player->Attack();
            play->CreateBullet(Bullet);
            CreateThread(NULL, 0, BulletTR, (LPVOID)Bullet, 0, NULL);
        }
        Sleep(100);
        //https://mlpworld.tistory.com/entry/Ű����-����-����
    }

    return 0;
}

void GameHandler::DeleteBullet(BulletBase* DelBullet)
{
    
    if (DelBullet == nullptr) return; // null ������ ������ ����
    
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

void GameHandler::CreateBullet(BulletBase* newBullet)
{
    
            WaitForSingleObject(Bullet_SemaHnd, INFINITE);
            Bullets.push_back(newBullet);
            ReleaseSemaphore(Bullet_SemaHnd, 1, NULL);

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

            if (result == false) // �� �ۿ� ���������
            {
                GetInstance()->DeleteBullet(Bullet);
                break;
            }
            Sleep(10);
        }
        
    }
    
    return 0;
}
