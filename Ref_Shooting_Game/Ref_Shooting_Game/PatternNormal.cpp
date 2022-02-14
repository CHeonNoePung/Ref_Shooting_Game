#include "PatternNormal.h"
#include "Bullet_Normal.h"
#include <math.h>

PatternNormal::PatternNormal(int Interval, int size) : PatternBase(Interval, size)
{
	bHomming = false;
}

PatternResult PatternNormal::Next(PatternParam Param)
{
	PatternResult result;

	RECT rect = Param.EntityRect;
	RECT playerRect = Param.PlayerRect;
	// ���߾� ��ġ ���
	POINT location;
	location.x = rect.left + (rect.right - rect.left) / 2 - BulletSize / 2;
	location.y = rect.top + (rect.bottom - rect.top) / 2 - BulletSize / 2;

	BulletBase* Bullet;
	if (bHomming == true)
	{
		POINT Dist_vec = { playerRect.left - location.x, playerRect.top - location.y };	// �Ÿ����� ����
		int Distance = (int)sqrt(pow(Dist_vec.x, 2) + pow(Dist_vec.y, 2));				// �Ÿ�����

		POINTF Unit_vec;
		Unit_vec.x = (float)Dist_vec.x / Distance;									// �������ͷ� ��ȯ
		Unit_vec.y = (float)Dist_vec.y / Distance;
	
		Bullet = new Bullet_Normal(location, Unit_vec);
	}
	else
		Bullet = new Bullet_Normal(location, POINTF{ 0, 3 });		//GetLocation() �� ���� ��ġ x,y ��ǥ��, POINTF �� �Ѿ� �ӵ� ����		
																	


	Bullet->SetSize(BulletSize, BulletSize);

	result.Bullet = Bullet;
	result.Interval = BulletInterval;

	return result;
}

void PatternNormal::SetHomming(bool bHomming)
{
	this->bHomming = bHomming;
}
