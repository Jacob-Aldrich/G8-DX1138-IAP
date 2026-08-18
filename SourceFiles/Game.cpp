#include "Game.h"
#include "Entity.h"
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
		[3] Return to the house
		[4] explore the world type shit
)";

	world = new World;
}

void Game::Run()
{
	int SafePlayerCount = 0;
	char Player = 'P';
	char Food = 'F';
	char Water = 'W';
	int PlayerInput;

	srand(static_cast<unsigned int>(time(0)));

	std::cout << "Running Game\n";

	//Entity* Enemies[3] =
	//{
	//	new Entity("Skinwalker1", true),
	//	new Entity("Skinwalker2", true),
	//	new Entity("Skinwalker3", true)
	//};

	//int random[2] = {
	//	rand() % 3,
	//	rand() % 3
	//};

	while (true)
	{
		std::cin >> PlayerInput;

		switch (PlayerInput)
		{
		case 1:
			world->SearchForSupplies();
			break;

		case 2:
			LookForSurvivors();
			break;

		case 3:
			std::cout << "You went back to the house\n";
			return;

		case 4:

			world->Explore();
			break;

		default:
			std::cout << "Invalid input\n";
			break;
		}
	}
	//for (int i = 0; i < 3; i++) {

	//	std::cout << "\n" << "You encountered " << Enemies[random[i]]->GetName() << "!\n";

	//	while (SafePlayers[random[i]]->IsAlive()) {

	//		SafePlayers[random[i]]->TakeDamage(Enemies[random[i]]->GetBaseAttackPoints());
	//		
	//		CheckIfDead(SafePlayers[random[i]]);

	//		if (SafePlayers[random[i]] == nullptr)
	//		{
	//			break;
	//		}

	//		std::cout << SafePlayers[random[i]]->GetName() << " has " << SafePlayers[random[i]]->GetHealthPoints() << " HP left! \n";
	//		
	//	}
	//}

	

	//int Enemy2Attack = Enemies[0].GetBaseAttackPoints();

	//Enemies[1].TakeDamage(Enemy2Attack);
	//int HPleft = Enemies[1].GetHealthPoints();
	//std::string enemyName = Enemies[1].GetName();
	//std::cout << enemyName << " " << HPleft << "\n";
}
void Game::CheckIfDead(Entity*& entity)
{
	if (entity->IsAlive() == false)
	{
		std::cout << entity->GetName() << " died and deleted\n";
		delete entity;
		entity = nullptr;
	}
}

void Game::LookForSurvivors()
{

	if (SafePlayerCount < 10)
	{
		int RandomName = rand() % 10;

		while (UsedNames[RandomName] == true)
		{
			RandomName = rand() % 10;
		}

		SafePlayers[SafePlayerCount] = new Entity(SafePlayerNames[RandomName], false);
		UsedNames[RandomName] = true;

		std::string Name = SafePlayers[SafePlayerCount]->GetName();
		int Attack = SafePlayers[SafePlayerCount]->GetBaseAttackPoints();
		int HP = SafePlayers[SafePlayerCount]->GetHealthPoints();

		std::cout << "You found " << Name << "!\n";
		std::cout << "Attack: " << Attack << "\n";
		std::cout << "HP:" << HP << "\n";

		SafePlayerCount++;
	}
	else
	{
		std::cout << "You cannot recruit any more survivors!\n";
	}
}
Game::~Game()
{
	delete world;
	std::cout << "Destructing Game\n";
}
