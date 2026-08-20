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
<<<<<<< HEAD

    int Hunger;
    int Thirst;

public:
    Entity(std::string startingName, int startingHealthPoints, int startingAttackPoints, bool startingSkinWalker, char startingSymbol);
=======

public:

    Entity(std::string startingName, bool startingIsSkinwalker);
>>>>>>> 8bd2a01c85ca3933a2de9f452fbd207a2bc2198c

    int GetHealthPoints();
    int GetBaseAttackPoints();

    std::string GetName();
    bool IsAlive();
    bool GetIsSkinWalker();
    void TakeDamage(int damagePoints);


};
