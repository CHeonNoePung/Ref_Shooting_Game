#pragma once
#include "EnemyBase.h"dsaewq

/*
오브젝트 클래스에 있는 드로우 오브젝트를 사용하고
각 몬스터 클래스에 멤버변수로 HBITMAP을 선언해서 각자 초기화 해줄것

*/
class Type0 : public EnemyBase
{
public:
	Type0();
	~Type0();


	static void SetCharacterBit(HINSTANCE hInst);

	void DrawObject(HDC hdc);
	
private:
	bool MoveNext();
	PatternResult Attack(PatternParam Param);

	class PatternNormal* patternNormal;
};

