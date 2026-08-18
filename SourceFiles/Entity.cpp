#include "Entity.h"
#include <string>

Entity::Entity(std::string startingName, bool startingIsSkinwalker)
{
    Name = startingName;
    HealthPoints = rand() % 41 + 80;
    AttackPoints = rand() % 4 + 2;
    IsSkinWalker = startingIsSkinwalker;
}

bool Entity::GetIsSkinWalker()
{
    return IsSkinWalker;
}
int Entity::GetHealthPoints()
{
    return HealthPoints;
}

int Entity::GetBaseAttackPoints()
{
    return AttackPoints;
}

std::string Entity::GetName()
{
    return Name;
}

bool Entity::IsAlive()
{
    return HealthPoints > 0;
}

void Entity::TakeDamage(int DamagePoints)
{
    HealthPoints -= DamagePoints;
}
