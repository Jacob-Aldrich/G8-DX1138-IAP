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

public:

    Entity(std::string startingName, int startingHealthPoints, int startingAttackPoints, bool startingSkinWalker);

    int GetHealthPoints();
    int GetBaseAttackPoints();

    std::string GetName();
    bool IsAlive();
    bool GetIsSkinWalker();
    void TakeDamage(int damagePoints);


};
