#include "Game.h"

Game::Game()
{
	std::cout << "Constructing Game\n";
	std::cout << 
		R"(You have 5 turns before nightfall.

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
		[3] Return to the house)";

	world = new World;
}

void Game::Run()
{
	std::cout << "Running Game\n";
}

Game::~Game()
{
	delete world;
	std::cout << "Destructing Game\n";
}
