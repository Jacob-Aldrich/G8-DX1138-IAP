#pragma once

#include "Object.h"

class Equipment;

// Character / creature game object.
class Entity : public Object
{
private:
    std::string Name;
    int HealthPoints;
    int MaximumHealthPoints;
    int AttackPoints;
    bool IsSkinWalker;

    int Hunger;
    int Thirst;

    // Recruited survivors can have one equipped item.
    // The Player keeps using Player::GetInventory() for its equipment.
    Equipment* EquippedGear;

public:
    Entity(std::string startingName, int startingHealthPoints, int startingAttackPoints, bool startingSkinWalker, char startingSymbol);
    virtual ~Entity();

    // jacob
    int GetHealthPoints();
    int GetBaseAttackPoints();

    std::string GetName();
    bool IsAlive();
    bool GetIsSkinWalker();
    void TakeDamage(int damagePoints);
    void RestoreHealth(int amount);
    int GetMaximumHealthPoints();

    int GetHunger();
    int GetThirst();

    void IncreaseHunger(int amount);
    void DecreaseHunger(int amount);

    void IncreaseThirst(int amount);
    void DecreaseThirst(int amount);

    Equipment* GetEquippedGear();
    bool EquipGear(Equipment* equipment);
    Equipment* UnequipGear();
};
