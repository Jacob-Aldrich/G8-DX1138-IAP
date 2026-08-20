#pragma once
#include "World.h"
#include "Entity.h"
#include <iostream>
#include <conio.h>
class Game
{
	World* world;
	int Turns;
	static int const maxTurns = 5;
<<<<<<< HEAD
	bool isRunning = false;
	bool isOutsideHouse = false;

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
	int SafePlayerCount = 0;
	bool UsedNames[10] = { false };
=======
	int SafePlayerCount = 0;

>>>>>>> 8bd2a01c85ca3933a2de9f452fbd207a2bc2198c
public:
	Game();
	void Run();

	int getTurns();
	void useTurn();
<<<<<<< HEAD
	//void randomScenario();
	//void randomSurvivor();
	//void randomSupply();
	void LookForSurvivors();
=======

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

>>>>>>> 8bd2a01c85ca3933a2de9f452fbd207a2bc2198c
	static void clearConsole();
	void displayInventory();
	void displaySurvivors();
	void displayStatus();
	void displayLegend();
	void displayCurrentChunk();
	~Game();
};

