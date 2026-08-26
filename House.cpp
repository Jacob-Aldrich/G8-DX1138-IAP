#include "House.h"
#include "Game.h"

House::House(char sym, int x, int y, std::string name, Game* g)
    : Object(sym, x, y, name), game(g), DoorDurability(MaximumDoorDurability)
{
}

int House::GetDoorDurability()
{
    return DoorDurability;
}

int House::GetMaximumDoorDurability()
{
    return MaximumDoorDurability;
}

bool House::IsDoorBroken()
{
    return DoorDurability <= 0;
}

void House::DamageDoor(int amount)
{
    if (amount < 0)
    {
        amount = 0;
    }

    DoorDurability -= amount;

    if (DoorDurability < 0)
    {
        DoorDurability = 0;
    }
}

void House::RepairDoor(int amount)
{
    if (amount < 0)
    {
        amount = 0;
    }

    DoorDurability += amount;

    if (DoorDurability > MaximumDoorDurability)
    {
        DoorDurability = MaximumDoorDurability;
    }
}

bool House::Interacted()
{
    game->goInsideHouse();
    return false;
}
