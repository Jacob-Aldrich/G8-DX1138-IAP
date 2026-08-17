#pragma once

#include "Object.h"

// character is a game object
class Entity : public Object
{
private:

    int HealthPoints;
    int AttackPoints;

public:

    Character(int startingHealthPoints, int startingAttackPoints);

    int GetHealthPoints();
    int GetBaseAttackPoints();

    bool IsAlive();

    void TakeDamage(int damagePoints);

    int Attack();
};
