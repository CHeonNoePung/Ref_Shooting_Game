
#include "EnemyBase.h"
class Enemy_turret :
    public EnemyBase
{
public:
    Enemy_turret();
    bool MoveNext();
    BulletBase* Attack();
    void DrawObject(HDC hdc);
};
