#include "Game.h"
#include "Entity.h"
#include "endings.h"
#include "skinwalker.h"
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

void Game::Battle()
{
    int PHealthPoints = 100;
    int PAttackPoints = 20;

    int skinwalkerHealth = std::rand() % 25 + 30;
    int skinwalkerAttack = std::rand() % 5 + 15;

    int battleChoice = 0;

    while (PHealthPoints > 0 && skinwalkerHealth > 0)
    {
		int turn = 1;

		std::cout << "========== TURN " << turn << " ==========" << std::endl;
        std::cout << "Your HP: " << PHealthPoints << std::endl;
        std::cout << "Skinwalker's HP: " << skinwalkerHealth << std::endl;

        displayImage();


        std::cout << "What will you do?" << std::endl;
        std::cout << "1. Attack" << std::endl;
        std::cout << "2. Item"<< std::endl;
        std::cout << "3. Run"<< std::endl;

        std::cin >> battleChoice;
	


        if (battleChoice == 1)
        {
            skinwalkerHealth -= PAttackPoints;

            std::cout << "You attack the Skinwalker for" << std::endl
                << PAttackPoints
                << " damage!" << std::endl;

			if (PAttackPoints > 30)
			{
				std::cout << "It was super effective!" << std::endl;
			}
			
			else if (PAttackPoints < 10)
			{
				std::cout << "It was not really effective" << std::endl;
			}

			else 
			{
				std::cout << " " << std::endl;
			}

            if (skinwalkerHealth < 0)
            {
                skinwalkerHealth = 0;
            }

            std::cout << "Skinwalker's HP:"
                << skinwalkerHealth << std::endl;
    
        }


        else if (battleChoice == 2)
        {
            std::cout << "You used an item!" << std::endl;

       /*  Can put the ACTUAL items here later 
	   * 
	   * 
            int healAmount = 20;

            PHealthPoints += healAmount;

            if (PHealthPoints > 100)
            {
                PHealthPoints = 100;
            }

            std::cout << "You recovered "
                << healAmount 
                << " HP!" << std::endl;

            std::cout << "Your HP: "
                << PHealthPoints
                << std::endl;*/
        }

        else if (battleChoice == 3)
        {
            int chance = std::rand() % 4; //25% chance to escape

            if (chance == 0)
            {
                std::cout << "You escaped from the Skinwalker!" << std::endl;
                return;
            }
            else
            {
                std::cout << "You failed to escape!" << std::endl;
            }
        }

        else
        {
            std::cout << "Pick a valid option." << std::endl;
            continue;
        }


        if (skinwalkerHealth <= 0)
        {
            std::cout << "You have defeated the Skinwalker!" << std::endl;

            return;
        }

        std::cout << "The Skinwalker attacks!" << std::endl;

        displayImage();

        PHealthPoints -= skinwalkerAttack;

        std::cout << "The Skinwalker deals "
            << skinwalkerAttack
            << " damage!" << std::endl;

		if (skinwalkerAttack > 15)
		{
			std::cout << "It was super effective!" << std::endl;
		}

		else if (skinwalkerAttack < 5)
		{
			std::cout << "It was not really effective" << std::endl;
		}

		else
		{
			std::cout << " " << std::endl;
		}

        if (PHealthPoints < 0)
        {
            PHealthPoints = 0;
        }

        std::cout << "Your HP: "
            << PHealthPoints
            << std::endl;


		if (PHealthPoints <= 0)
		{
			std::cout << "You have been defeated by the Skinwalker!" << std::endl;

			endings ending;
			ending.DeathEnding();

			return;
		}
		turn++;
    }
}

Game::~Game()
{
	delete world;
	std::cout << "Destructing Game\n";
}
