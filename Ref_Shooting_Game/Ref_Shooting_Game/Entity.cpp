#include "Entity.h"

int Entity::GetHealth() {

	return Health;
}

void Entity::SetHealth(int newHealth) {
	Health = newHealth;
}

bool Entity::GetDamages(int x)
{
	return false;
}

BulletBase* Entity::Attack()
{
	return nullptr;
}
	