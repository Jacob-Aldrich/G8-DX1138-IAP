#pragma once

#include "Object.h"

// character is a game object
class Entity : public Object
{
private:

    std::string Name;
    int HealthPoints;
    int AttackPoints;
    bool IsSkinWalker;

    int Hunger;
    int Thirst;

public:
    Entity(std::string startingName, int startingHealthPoints, int startingAttackPoints, bool startingSkinWalker, char startingSymbol);

    int GetHealthPoints();
    int GetBaseAttackPoints();

    void AddHunger(int amount);
    void AddThirst(int amount);

    int GetHunger();
    int GetThirst();

    std::string GetName();
    bool IsAlive();
    bool GetIsSkinWalker();

    void TakeDamage(int damagePoints);
};