#pragma warning(disable:4828)
#include "Stage.h"
#include "Type0.h"
#include "Enemy_bird.h"
#include "Enemy_turret.h"
#include "Enemy_MiddleBoss.h"

/*
 Rectangle(hdc, 400, 10, 1000, 690)// 게임 배경

 게임 핸들러가 모든 정보를 다 가지고 있음(몬스터, 플레이어, 총알에 관한 정보 등을)

 이 상태에서 스테이지를 클래스로 따로 만들려고 만지작거리면 거릴수록 드는 생각이
 스테이지 클래스 안에 GameHandler를 넣는 수 밖에 없다는 생각이 듦
 이럴경우 스테이지를 클래스로 따로 만드는 의미가 없음 그냥 GameHandler가 하나의 스테이지임
 GameHandler 안에 보스몹이랑 잡몹 추가하면 끝나는거임


 만약,
 스테이지를 클래스로 만든다하면 몬스터, 플레이어, 총알정보 등을 클래스로 만들어두고
 스테이지 안에서 new로 불러서 해야될것 같음


*/

Stage::Stage()
{
	Monster_Number = 0;
}

Stage::~Stage()
{
	
}


EnemyBase* Stage::getMonsterBase()
{
	EnemyBase* Enemy = nullptr;
	// case 뒤에 숫자가 순서임 만약 슬라임 슬라임 소환하고 싶으면 case 0,1을 슬라임으로 두면 됨
	// 소환할 몹을 쭈르륵 나열하면 됨
	switch(Monster_Number)
	{
	case 0:
	{
		//new 슬라임;
		Enemy = new Enemy_bird();
		Enemy->SetLocation(POINT{ 750,70 }); // 좌표 설정
	}
	break;
	case 1:
	{
		Sleep(500);
		//new 초록버섯;
		Enemy = new Enemy_turret();
		Enemy->SetLocation(POINT{ 750,70 }); // 좌표 설정
	}
	break;
	case 2: 
	{
		Sleep(500);
		//new 주니어발록 
		Enemy = new Type0(); // 생성
		Enemy->SetLocation(POINT{ 700,20 }); // 좌표 설정
	}
	break;
	case 3: {
		Sleep(500);
		Enemy = new Enemy_MiddleBoss(); // 생성
		//Enemy->SetLocation(POINT{ 700,70 }); // 좌표 설정
	
	}
	break;
	default:
		break;
	}
	Monster_Number++;

	return Enemy;
}
