#pragma once
#include "Object.h"

class Game;

class House : public Object
{
private:
    Game* game;
    static const int MaximumDoorDurability = 100;
    int DoorDurability;

public:
    House(char sym, int x, int y, std::string name, Game* game);

    int GetDoorDurability();
    int GetMaximumDoorDurability();
    bool IsDoorBroken();
    void DamageDoor(int amount);
    void RepairDoor(int amount);

    bool Interacted() override;
};
