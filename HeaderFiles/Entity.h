#pragma once
#include <string>
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

    Entity(std::string startingName, bool startingIsSkinwalker);

    int GetHealthPoints();
    int GetBaseAttackPoints();

    std::string GetName();
    bool IsAlive();
    bool GetIsSkinWalker();
    void TakeDamage(int damagePoints);


};
