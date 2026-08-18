#pragma once
#include "World.h"
#include <iostream>
class Game
{
	World* world;
	int Turns;
	static int const maxTurns = 5;
	int SafePlayerCount = 0;

public:
	Game();
	void Run();

	int getTurns();
	void useTurn();

	void LookForSurvivors();
    bool UsedNames[10] = { false };
    std::string SafePlayerNames[10] =
    {
        "James",
        "Ethan",
        "Marcus",
        "Daniel",
        "Ryan",
        "Lucas",
        "Adrian",
        "Noah",
        "Jason",
        "Kevin"
    };

    Entity* SafePlayers[10] = { nullptr };

	void CheckIfDead(Entity*& entity);

	static void clearConsole();
	~Game();
};

