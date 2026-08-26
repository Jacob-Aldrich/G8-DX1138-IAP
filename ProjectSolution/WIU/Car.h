#pragma once

#include "Object.h"
//jacob

class Game;

class Car : public Object
{
private:
    Game* game;

public:
    Car(int startingX, int startingY, Game* startingGame);

    bool Interacted() override;
};