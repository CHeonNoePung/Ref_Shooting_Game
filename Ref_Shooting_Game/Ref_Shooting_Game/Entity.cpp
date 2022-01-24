#include "Entity.h"

int Entity::GetHealth() {

	return Health;
}

void Entity::SetHealth(int newHealth) {
	Health = newHealth;
}

BulletBase* Entity::Attack()
{
	return nullptr;
}
	