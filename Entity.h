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

    std::string GetName();
    bool IsAlive();
    bool GetIsSkinWalker();
    void TakeDamage(int damagePoints);

	int GetHunger();
	int GetThirst();

	void IncreaseHunger(int amount);
	void DecreaseHunger(int amount);

	void IncreaseThirst(int amount);
	void DecreaseThirst(int amount);
};
