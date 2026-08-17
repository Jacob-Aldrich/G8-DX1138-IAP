#include "Game.h"
#include "World.h"

Game::Game()
{
	world = new World;
	char choice;

	std::cout << "Constructing Game\n";
	std::cout << 
		R"(
You have 5 turns before nightfall.

Recruit survivors.
Gather food.
Find water.
Collect useful supplies.

Choose carefully.

Every person you save is another mouth
to feed.

And not everyone you meet is human.

Turns Remaining : 5

> What will you do?

[1] Search for supplies
[2] Look for survivors
[3] Return to the house --THIS WILL SKIP ALL TURNS
)";

	for (int i = 0; i < 5; i++) {
		std::cin >> choice;

		if (choice == '1') {
			std::cout << "Searching for supplies";
			
		}
		else if (choice == '2') {
			std::cout << "Looking for survivors";
			
		}
		else if (choice == '3') {
			std::cout << "Returning to the house";
			break;
		}
	}
}

void Game::Run()
{
	Turns = 5;

	std::cout << "Running Game\n";
}


int Game::getTurns()
{
	return Turns;
}

void Game::useTurn()
{
	Turns--;
	if (Turns <= 0) {
		Turns = maxTurns;
	}
}

void Game::clearConsole()
{
	std::cout << "\033[H\033[2J";
}

Game::~Game()
{
	delete world;
	std::cout << "Destructing Game\n";
}