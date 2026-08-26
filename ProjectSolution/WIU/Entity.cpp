#include "Entity.h"
#include "Equipment.h"
//wenya and shanelle

Entity::Entity(std::string startingName, int startingHealthPoints, int startingAttackPoints, bool startingIsSkinWalker, char startingSymbol)
    : Object(startingSymbol, 0, 0, startingName)
{
    Name = startingName;
    HealthPoints = startingHealthPoints;
    AttackPoints = startingAttackPoints;
    IsSkinWalker = startingIsSkinWalker;
    MaximumHealthPoints = startingHealthPoints;
    Hunger = 100;
    Thirst = 100;
    EquippedGear = nullptr;
}

Entity::~Entity()
{
    delete EquippedGear;
    EquippedGear = nullptr;
}

bool Entity::GetIsSkinWalker() { return IsSkinWalker; }
int Entity::GetHealthPoints() { return HealthPoints; }
int Entity::GetBaseAttackPoints() { return AttackPoints; }
std::string Entity::GetName() { return Name; }
bool Entity::IsAlive() { return HealthPoints > 0; }

void Entity::TakeDamage(int DamagePoints)
{
    HealthPoints -= DamagePoints;
}

// jacob
void Entity::RestoreHealth(int amount)
{
    HealthPoints += amount;

    if (HealthPoints > MaximumHealthPoints)
    {
        HealthPoints = MaximumHealthPoints;
    }
}

int Entity::GetMaximumHealthPoints()
{
    return MaximumHealthPoints;
}

int Entity::GetHunger() { return Hunger; }
int Entity::GetThirst() { return Thirst; }

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

Equipment* Entity::GetEquippedGear() { return EquippedGear; }

bool Entity::EquipGear(Equipment* equipment)
{
    if (equipment == nullptr || EquippedGear != nullptr)
    {
        return false;
    }

    EquippedGear = equipment;
    return true;
}

Equipment* Entity::UnequipGear()
{
    Equipment* gear = EquippedGear;
    EquippedGear = nullptr;
    return gear;
}
