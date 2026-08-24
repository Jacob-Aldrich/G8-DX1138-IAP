#pragma once
#include "Object.h"

class Game;
class House : public Object
{
	Game* game;
public:
	House(char sym, int x, int y, std::string name, Game* game);
	bool Interacted() override;
};

