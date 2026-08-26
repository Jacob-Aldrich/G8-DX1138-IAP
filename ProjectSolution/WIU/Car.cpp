#include "Car.h"
#include "Game.h"
//jacob
Car::Car(int startingX, int startingY, Game* startingGame) : Object('C', startingX, startingY, "Signal Car")

{
    game = startingGame;
}

bool Car::Interacted()
{
    if (game == nullptr)
    {
        return false;
    }

    game->CallHelicopter();

    // False prevents the car from being collected into the inventory.
    return false;
}