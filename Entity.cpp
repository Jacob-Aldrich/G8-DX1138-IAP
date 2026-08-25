#include "Entity.h"

Entity::Entity(std::string startingName, int startingHealthPoints, int startingAttackPoints, bool startingIsSkinWalker, char startingSymbol) : Object(startingSymbol, 0, 0, startingName)
{
    Name = startingName;
    HealthPoints = startingHealthPoints;
    AttackPoints = startingAttackPoints;
    IsSkinWalker = startingIsSkinWalker;
    Hunger = 100;
    Thirst = 100;

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

int Entity::GetHunger()
{
    return Hunger;
}

int Entity::GetThirst()
{
    return Thirst;
}

void Entity::IncreaseHunger(int amount)
{
    Hunger += amount;
    if (Hunger > 100)
    {
        Hunger = 100;
    }
}

void Entity::DecreaseHunger(int amount)
{
    Hunger -= amount;
    if (Hunger < 0)
    {
        Hunger = 0;
    }
}

void Entity::IncreaseThirst(int amount)
{
    Thirst += amount;
    if (Thirst > 100)
    {
        Thirst = 100;
    }
}

void Entity::DecreaseThirst(int amount)
{
    Thirst -= amount;
    if (Thirst < 0)
    {
        Thirst = 0;
    }
}
