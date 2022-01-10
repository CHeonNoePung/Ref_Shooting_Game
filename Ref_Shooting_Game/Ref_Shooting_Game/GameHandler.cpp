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

DWORD WINAPI GameHandler::BulletTR(LPVOID param)
{
    BulletBase* Bullet = (BulletBase*)param;
    if (Bullet != nullptr)
    {
        while (1)
        {
            bool result = Bullet->MoveNext();
            InvalidateRect(hWnd, NULL, false);

            if (result == false) // ¸Ê ¹Û¿¡ ³ª°¬À»°æ¿ì
                break;
            Sleep(10);
        }
        
    }
    
    return 0;
}
