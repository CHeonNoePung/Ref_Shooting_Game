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

void Entity::SetType(int x)
{
	this->Type = x;
}

int Entity::GetType()
{
	return this->Type;
}
