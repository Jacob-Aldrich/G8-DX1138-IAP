#include "Entity.h"
#include <string>

<<<<<<< HEAD
Entity::Entity(std::string startingName, int startingHealthPoints, int startingAttackPoints, bool startingIsSkinWalker, char startingSymbol) : Object(startingSymbol, 0, 0, startingName)
{
    Name = startingName;
    HealthPoints = startingHealthPoints;
    AttackPoints = startingAttackPoints;
    IsSkinWalker = startingIsSkinWalker;

=======
Entity::Entity(std::string startingName, bool startingIsSkinwalker)
{
    Name = startingName;
    HealthPoints = rand() % 41 + 80;
    AttackPoints = rand() % 4 + 2;
    IsSkinWalker = startingIsSkinwalker;
>>>>>>> 8bd2a01c85ca3933a2de9f452fbd207a2bc2198c
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
<<<<<<< HEAD
}
=======
}
>>>>>>> 8bd2a01c85ca3933a2de9f452fbd207a2bc2198c
