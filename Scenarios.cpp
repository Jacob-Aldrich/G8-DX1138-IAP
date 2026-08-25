#include "Scenarios.h"
#include "Game.h"
#include <cstdlib>
#include <iostream>

Scenarios::Scenarios()
{
}

void Scenarios::ChooseRandomEvent(Game* game)
{
    if (game == nullptr)
        return;

    // A scenario is only rolled after a turn while the player is inside.
    // This function is called by Game::useTurn(), so no outside event can
    // accidentally trigger here.
    const int scenarioChance = 35;
    if (rand() % 100 >= scenarioChance)
        return;

    int type = rand() % 4;

    std::cout << "\n\n========== HOUSE SCENARIO ==========\n";

    switch (type)
    {
    case SEND_SOMEONE_EVENT:
    {
        // Send a living survivor to investigate a noise outside.
        int candidates[10];
        int count = 0;

        for (int i = 1; i < game->SafePlayerCount; ++i)
        {
            if (game->SafePlayers[i] != nullptr &&
                game->SafePlayers[i]->IsAlive())
            {
                candidates[count++] = i;
            }
        }

        if (count == 0)
        {
            std::cout << "You hear a noise outside, but there is nobody to send.\n";
            break;
        }

        std::cout << "A noise comes from outside the house.\n";
        std::cout << "Send someone to investigate? [Y/N]: ";

        char answer;
        std::cin >> answer;

        if (answer == 'y' || answer == 'Y')
        {
            Entity* survivor = game->SafePlayers[candidates[rand() % count]];

            if (rand() % 2 == 0)
            {
                int food = 1 + rand() % 2;
                game->world->GetFood()->AddQuantity(food);
                std::cout << survivor->GetName()
                          << " returns with " << food << " food.\n";
            }
            else
            {
                int damage = 5 + rand() % 11;
                survivor->TakeDamage(damage);
                std::cout << survivor->GetName()
                          << " was attacked while investigating and took "
                          << damage << " damage.\n";
            }
        }
        else
        {
            std::cout << "You decide it is safer to stay inside.\n";
        }
        break;
    }

    case YES_OR_NO_EVENT:
    {
        std::cout << "You hear scratching at the front door.\n";
        std::cout << "Do you reinforce the door? [Y/N]: ";

        char answer;
        std::cin >> answer;

        if (answer == 'y' || answer == 'Y')
        {
            if (!game->world->GetWater()->IsEmpty())
            {
                game->world->GetWater()->UseQuantity(1);
                std::cout << "You use 1 water to keep everyone calm while "
                             "the door is secured.\n";
            }
            else
            {
                std::cout << "The group reinforces the door with whatever is available.\n";
            }
        }
        else
        {
            if (!game->world->GetFood()->IsEmpty())
            {
                game->world->GetFood()->UseQuantity(1);
                std::cout << "The noise continues. Someone eats 1 food from stress.\n";
            }
            else
            {
                std::cout << "The scratching continues for a while, then stops.\n";
            }
        }
        break;
    }

    case ITEMS_EVENT:
    {
        int food = rand() % 3;
        int water = rand() % 3;

        game->world->GetFood()->AddQuantity(food);
        game->world->GetWater()->AddQuantity(water);

        std::cout << "While checking the house, you discover a hidden stash: +"
                  << food << " food and +" << water << " water.\n";
        break;
    }

    case CHOOSE_SOMEONE_EVENT:
    {
        int candidates[10];
        int count = 0;

        std::cout << "The group needs someone to keep watch tonight.\n";
        for (int i = 1; i < game->SafePlayerCount; ++i)
        {
            if (game->SafePlayers[i] != nullptr &&
                game->SafePlayers[i]->IsAlive())
            {
                candidates[count++] = i;
                std::cout << "[" << count << "] "
                          << game->SafePlayers[i]->GetName()
                          << " | HP: "
                          << game->SafePlayers[i]->GetHealthPoints() << "\n";
            }
        }

        if (count == 0)
        {
            std::cout << "There are no companions available to keep watch.\n";
            break;
        }

        std::cout << "Choose someone (1-" << count << "): ";

        int choice;
        std::cin >> choice;

        if (choice < 1 || choice > count)
        {
            std::cout << "Invalid choice. Nobody is assigned to watch.\n";
            break;
        }

        Entity* survivor = game->SafePlayers[candidates[choice - 1]];
        int damage = 3 + rand() % 8;
        survivor->TakeDamage(damage);

        std::cout << survivor->GetName()
                  << " keeps watch and becomes exhausted, losing "
                  << damage << " HP.\n";
        break;
    }
    }

    std::cout << "===================================\n";
}
