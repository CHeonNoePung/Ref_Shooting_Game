#include "Enemy_bird.h"
#include "Bullet_Normal.h"

Enemy_bird::Enemy_bird()
{
	SetHealth(3);
	SetSize(50, 50);
	SetLocation(POINT{ 700, 20});
	test_sin = 45;
	std::cout << Location.x << "  "<<Location.y << std::endl;
}

void Enemy_bird::DrawObject(HDC hdc)
{
	RECT temp = GetRect();
	Ellipse(hdc, temp.left, temp.top, temp.right, temp.bottom);
}

bool Enemy_bird::MoveNext() 
{
	//Rectangle(hdc, 400, 10, 1000, 690) 화면 사이즈
	Location = POINT{ Location.x , Location.y };

	
		Location.x = 400 + 0.03 * test_sin * test_sin ;
		Location.y += 10;
		test_sin -= 4;
	

	//std::cout << 400 + 0.03 * test_sin * test_sin << "  " << test_sin << "\n"<< std::endl;
	//std::cout << Location.x << "  " << Location.y << std::endl;
	if (10 > Location.y || Location.y > 690) return false;
	else if (400 > Location.x || Location.x > 1000) return false;
	else return true;
}


BulletBase* Enemy_bird::Attack()
{
	POINT location = GetLocation();

	location.x += GetSize().x / 2 - 5 / 2;
	location.y += GetSize().y / 2 - 5 / 2;

	BulletBase* Bullet = new Bullet_Normal(location, POINTF{ 0, 3 }, 1);
	Bullet->SetSize(5, 5);
	return Bullet;
}



