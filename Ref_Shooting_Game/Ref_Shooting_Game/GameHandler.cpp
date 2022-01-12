#include "GameHandler.h"
#include "PlayerBase.h"
#include "Bullet_Normal.h"
#include <iostream>

GameHandler* GameHandler::Instance = nullptr;
HWND GameHandler::hWnd = NULL;

GameHandler::GameHandler()
{
    player = new PlayerBase();
}
void GameHandler::OnPaint(HDC hdc)
{
    
    player->DrawObject(hdc);
    for (int i = 0; i < Bullets.size(); i++)
    {
        if (Bullets[i] != nullptr)
        {
            Bullets[i]->DrawObject(hdc);
        }
    }
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
            if (player->GetLocation().y <= 900) // 여기다가 하면 됨
            {
                player->SetLocation(POINT{ player->GetLocation().x, player->GetLocation().y + 3 });
                InvalidateRect(hWnd, NULL, FALSE);
            }
        }
        if (GetKeyState(0x44) & 0x8000) //d
        {
            if (player->GetLocation().x <= 1080) // 여기다가 하면 됨
            {
                player->SetLocation(POINT{ player->GetLocation().x + 3, player->GetLocation().y });
                InvalidateRect(hWnd, NULL, FALSE);
            }
        }
        Sleep(20);
        //https://mlpworld.tistory.com/entry/키보드-상태-조사
    }

    return 0;
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

            if (result == false) // 맵 밖에 나갔을경우
                break;
            Sleep(10);
        }
        
    }
    
    return 0;
}
