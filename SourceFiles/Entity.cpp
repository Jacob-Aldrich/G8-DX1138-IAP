#include "Entity.h"

Entity::Entity(int startingHealthPoints, int startingAttackPoints)
{
    HealthPoints = startingHealthPoints;
    AttackPoints = startingAttackPoints;
}

int Entity::GetHealthPoints()
{
    return HealthPoints;
}

int Entity::GetBaseAttackPoints()
{
    return AttackPoints;
}

bool Entity::IsAlive()
{
    return HealthPoints > 0;
}

void Entity::TakeDamage(int DamagePoints)
{
    if (DamagePoints >= HealthPoints)
    {
        HealthPoints = 0;
    }
    else
    {
        HealthPoints -= DamagePoints;
    }
}

int Entity::Attack()
{
    return AttackPoints;
}
