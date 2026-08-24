#include "Entity.h"

Entity::Entity(std::string startingName, int startingHealthPoints, int startingAttackPoints, bool startingIsSkinWalker, char startingSymbol) : Object(startingSymbol, 0, 0, startingName)
{
    Name = startingName;
    HealthPoints = startingHealthPoints;
    AttackPoints = startingAttackPoints;
    IsSkinWalker = startingIsSkinWalker;

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