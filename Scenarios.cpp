#include "Scenarios.h"
#include "ConsoleColors.h"
#include "Game.h"
#include "skinwalker.h"

#include <cstdlib>
#include <iostream>

Scenarios::Scenarios()
{
}

void Scenarios::ChooseRandomEvent(Game* game)
{
    if (game == nullptr)
    {
        return;
    }

    // A scenario is only rolled after a turn while the player is inside.
    const int scenarioChance = 35;

    if (rand() % 100 >= scenarioChance)
    {
        return;
    }

    ScenarioTypes type = static_cast<ScenarioTypes>(rand() % 4);

    std::cout << "\n\n";
    ConsoleColor::Print("========== HOUSE SCENARIO ==========\n", ConsoleColor::BRIGHT_MAGENTA);

    switch (type)
    {
    case SEND_SOMEONE_EVENT:
        RunSendSomeoneEvent(game);
        break;

    case YES_OR_NO_EVENT:
        RunYesOrNoEvent(game);
        break;

    case ITEMS_EVENT:
        RunItemsEvent(game);
        break;

    case CHOOSE_SOMEONE_EVENT:
        RunChooseSomeoneEvent(game);
        break;
    }

    ConsoleColor::Print("====================================\n", ConsoleColor::BRIGHT_MAGENTA);
}

void Scenarios::RunSendSomeoneEvent(Game* game)
{
    // SEND_SOMEONE_EVENT is a TYPE. One of several concrete scenarios is
    // selected after the type itself has already been chosen.
    const int scenario = rand() % 3;

    int candidates[10];
    int count = 0;

    for (int i = 1; i < game->SafePlayerCount; i++)
    {
        if (game->SafePlayers[i] != nullptr && game->SafePlayers[i]->IsAlive())
        {
            candidates[count] = i;
            count++;
        }
    }

    if (scenario == 0)
    {
        ConsoleColor::Print("A noise comes from the alley behind the house.\n", ConsoleColor::YELLOW);

        if (count == 0)
        {
            std::cout << "There is nobody available to send outside.\n";
            return;
        }

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
                ConsoleColor::Print(survivor->GetName(), ConsoleColor::BRIGHT_CYAN);
                std::cout << " returns with " << food << " food.\n";
            }
            else
            {
                int damage = 5 + rand() % 11;
                survivor->TakeDamage(damage);
                ConsoleColor::Print(survivor->GetName(), ConsoleColor::BRIGHT_CYAN);
                std::cout << " was attacked and took " << damage << " damage.\n";
            }
        }
        else
        {
            std::cout << "You keep everyone inside and ignore the sound.\n";
        }
    }
    else if (scenario == 1)
    {
        ConsoleColor::Print("Someone spots an abandoned delivery bag across the street.\n", ConsoleColor::YELLOW);

        if (count == 0)
        {
            std::cout << "Nobody can safely retrieve it.\n";
            return;
        }

        std::cout << "Send a survivor to grab it? [Y/N]: ";
        char answer;
        std::cin >> answer;

        if (answer == 'y' || answer == 'Y')
        {
            Entity* survivor = game->SafePlayers[candidates[rand() % count]];
            int result = rand() % 3;

            if (result == 0)
            {
                int damage = 8 + rand() % 8;
                survivor->TakeDamage(damage);
                std::cout << "It was bait. ";
                ConsoleColor::Print(survivor->GetName(), ConsoleColor::BRIGHT_CYAN);
                std::cout << " escapes but loses " << damage << " HP.\n";
            }
            else
            {
                int food = 1 + rand() % 3;
                int water = 1 + rand() % 2;
                game->world->GetFood()->AddQuantity(food);
                game->world->GetWater()->AddQuantity(water);
                ConsoleColor::Print(survivor->GetName(), ConsoleColor::BRIGHT_CYAN);
                std::cout << " returns safely with +" << food << " food and +" << water << " water.\n";
            }
        }
        else
        {
            std::cout << "You decide the bag is not worth the risk.\n";
        }
    }
    else
    {
        ConsoleColor::Print("An injured stranger collapses near the front gate.\n", ConsoleColor::YELLOW);

        if (count == 0)
        {
            std::cout << "Nobody is available to check on them, so you stay behind the door.\n";
            return;
        }

        std::cout << "Send someone to check if they are alive? [Y/N]: ";
        char answer;
        std::cin >> answer;

        if (answer == 'y' || answer == 'Y')
        {
            Entity* survivor = game->SafePlayers[candidates[rand() % count]];

            if (rand() % 100 < 65)
            {
                std::cout << "The stranger is human and grateful for the help.\n";

                if (game->SafePlayerCount < 4)
                {
                    game->LookForSurvivors();
                }
                else
                {
                    game->world->GetWater()->AddQuantity(1);
                    std::cout << "Your shelter is full, so the stranger leaves you 1 water instead.\n";
                }
            }
            else
            {
                int damage = 6 + rand() % 10;
                survivor->TakeDamage(damage);
                std::cout << "The stranger lashes out and runs. ";
                ConsoleColor::Print(survivor->GetName(), ConsoleColor::BRIGHT_CYAN);
                std::cout << " takes " << damage << " damage.\n";
            }
        }
        else
        {
            std::cout << "You leave the stranger outside. By morning, they are gone.\n";
        }
    }
}

void Scenarios::StartHouseAttackCombat(Game* game, bool skinwalkerAttack)
{
    if (game == nullptr || game->Fighting || game->player == nullptr || !game->player->IsAlive())
    {
        return;
    }

    game->ClearCombat();

    for (int i = 0; i < 3; i++)
    {
        game->ActiveParty[i] = nullptr;
    }

    game->ActivePartyCount = 0;

    // The combat system supports a party of three, so the player and up to
    // two living survivors defend the house together.
    for (int i = 0; i < game->SafePlayerCount && game->ActivePartyCount < 3; i++)
    {
        if (game->SafePlayers[i] != nullptr && game->SafePlayers[i]->IsAlive())
        {
            game->ActiveParty[game->ActivePartyCount] = game->SafePlayers[i];
            game->ActivePartyCount++;
        }
    }

    if (game->ActivePartyCount == 0)
    {
        return;
    }

    game->EnemyCount = 1 + rand() % 2;

    for (int i = 0; i < game->EnemyCount; i++)
    {
        int hp = 45 + rand() % 36;
        int atk = 6 + rand() % 5;

        if (skinwalkerAttack)
        {
            game->Enemies[i] = new Entity(
                "Skinwalker " + std::to_string(i + 1), hp, atk, true, 'X');
        }
        else
        {
            game->Enemies[i] = new Entity(
                "Raider " + std::to_string(i + 1), hp, atk, false, 'R');
        }
    }

    std::cout << "\n";
    ConsoleColor::Print("!!! THE HOUSE IS UNDER ATTACK !!!\n", ConsoleColor::BRIGHT_RED);
    game->RunCombat();

    for (int i = 0; i < 3; i++)
    {
        game->ActiveParty[i] = nullptr;
    }

    game->ActivePartyCount = 0;
}

void Scenarios::RunYesOrNoEvent(Game* game)
{
    const int scenario = rand() % 4;

    if (scenario == 0)
    {
        ConsoleColor::Print("A frightened survivor knocks on the door asking for shelter.\n", ConsoleColor::BRIGHT_YELLOW);
        std::cout << "Let them inside? [Y/N]: ";

        char answer;
        std::cin >> answer;

        if (answer == 'y' || answer == 'Y')
        {
            if (game->SafePlayerCount < 4)
            {
                game->LookForSurvivors();
            }
            else
            {
                std::cout << "There is no room for another survivor.\n";
            }
        }
        else
        {
            std::cout << "You refuse. The survivor disappears into the night.\n";
        }
    }
    else if (scenario == 1)
    {
        ConsoleColor::Print("A stranger stands perfectly still outside your door.\n", ConsoleColor::BRIGHT_YELLOW);

        Skinwalker stranger("Stranger");
        stranger.dialogue();

        std::cout << "Let the stranger inside? [Y/N]: ";
        char answer;
        std::cin >> answer;

        if (answer == 'y' || answer == 'Y')
        {
            skinwalkerjumpscare::ShowSkinwalkerJumpscare();
            game->house->DamageDoor(15);
            StartHouseAttackCombat(game, true);
        }
        else
        {
            if (rand() % 2 == 0)
            {
                std::cout << "The stranger smiles too widely and walks away.\n";
            }
            else
            {
                int damage = 10 + rand() % 16;
                game->house->DamageDoor(damage);
                ConsoleColor::Print("The stranger SLAMS into the door before vanishing.\n", ConsoleColor::BRIGHT_RED);
                std::cout << "Door damage: " << damage << ".\n";
            }
        }
    }
    else if (scenario == 2)
    {
        ConsoleColor::Print("Hostile raiders surround the house.\n", ConsoleColor::BRIGHT_RED);
        std::cout << "Fight them before they break through? [Y/N]: ";

        char answer;
        std::cin >> answer;

        if (answer == 'y' || answer == 'Y')
        {
            StartHouseAttackCombat(game, false);
        }
        else
        {
            int damage = 15 + rand() % 21;
            game->house->DamageDoor(damage);
            std::cout << "You stay quiet while they attack the entrance. Door damage: " << damage << ".\n";

            if (game->house->IsDoorBroken())
            {
                ConsoleColor::Print("THE DOOR BREAKS. THEY GET INSIDE.\n", ConsoleColor::BRIGHT_RED);
                StartHouseAttackCombat(game, false);
            }
            else if (rand() % 2 == 0 && !game->world->GetFood()->IsEmpty())
            {
                game->world->GetFood()->UseQuantity(1);
                std::cout << "The raiders steal 1 food through a broken section before leaving.\n";
            }
            else
            {
                std::cout << "Eventually the raiders leave, but the door is weaker.\n";
            }
        }
    }
    else
    {
        ConsoleColor::Print("The damaged door is beginning to split around the lock.\n", ConsoleColor::YELLOW);
        std::cout << "Repair it immediately? [Y/N]: ";

        char answer;
        std::cin >> answer;

        if (answer == 'y' || answer == 'Y')
        {
            int repair = 20 + rand() % 21;
            game->house->RepairDoor(repair);
            std::cout << "You reinforce the entrance and restore " << repair << " door durability.\n";
        }
        else
        {
            int damage = 5 + rand() % 11;
            game->house->DamageDoor(damage);
            std::cout << "The crack gets worse. The door loses another " << damage << " durability.\n";
        }
    }
}

void Scenarios::RunItemsEvent(Game* game)
{
    const int scenario = rand() % 3;

    if (scenario == 0)
    {
        int food = rand() % 3;
        int water = rand() % 3;

        game->world->GetFood()->AddQuantity(food);
        game->world->GetWater()->AddQuantity(water);

        ConsoleColor::Print("You discover a hidden stash inside the house.\n", ConsoleColor::BRIGHT_GREEN);
        std::cout << "+" << food << " food and +" << water << " water.\n";
    }
    else if (scenario == 1)
    {
        ConsoleColor::Print("A sealed emergency crate is wedged behind an old cabinet.\n", ConsoleColor::BRIGHT_GREEN);
        std::cout << "Force it open? [Y/N]: ";

        char answer;
        std::cin >> answer;

        if (answer == 'y' || answer == 'Y')
        {
            if (rand() % 100 < 70)
            {
                int food = 1 + rand() % 3;
                int water = 1 + rand() % 3;
                game->world->GetFood()->AddQuantity(food);
                game->world->GetWater()->AddQuantity(water);
                std::cout << "Success: +" << food << " food and +" << water << " water.\n";
            }
            else
            {
                int damage = 5 + rand() % 11;
                game->player->TakeDamage(damage);
                ConsoleColor::Print("A rusted metal edge cuts your arm.\n", ConsoleColor::BRIGHT_RED);
                std::cout << "You lose " << damage << " HP.\n";
            }
        }
        else
        {
            std::cout << "You leave the crate alone.\n";
        }
    }
    else
    {
        ConsoleColor::Print("You find several old cans in a forgotten cupboard.\n", ConsoleColor::BRIGHT_GREEN);

        if (rand() % 2 == 0)
        {
            int food = 1 + rand() % 2;
            game->world->GetFood()->AddQuantity(food);
            std::cout << "They are still edible. +" << food << " food.\n";
        }
        else
        {
            int damage = 4 + rand() % 7;
            game->player->TakeDamage(damage);
            std::cout << "One can bursts with spoiled contents. You lose " << damage << " HP.\n";
        }
    }
}

void Scenarios::RunChooseSomeoneEvent(Game* game)
{
    const int scenario = rand() % 3;

    int candidates[10];
    int count = 0;

    for (int i = 1; i < game->SafePlayerCount; i++)
    {
        if (game->SafePlayers[i] != nullptr && game->SafePlayers[i]->IsAlive())
        {
            candidates[count] = i;
            count++;
        }
    }

    if (count == 0)
    {
        std::cout << "There are no living companions available for this task.\n";
        return;
    }

    if (scenario == 0)
    {
        ConsoleColor::Print("Someone needs to keep watch tonight.\n", ConsoleColor::YELLOW);
    }
    else if (scenario == 1)
    {
        ConsoleColor::Print("The front door needs hands-on repairs before the next attack.\n", ConsoleColor::YELLOW);
    }
    else
    {
        ConsoleColor::Print("A stranger wants to trade supplies, but somebody must meet them outside.\n", ConsoleColor::YELLOW);
    }

    for (int i = 0; i < count; i++)
    {
        Entity* survivor = game->SafePlayers[candidates[i]];
        std::cout << "[" << i + 1 << "] " << survivor->GetName()
                  << " | HP: " << survivor->GetHealthPoints() << "\n";
    }

    std::cout << "Choose someone (1-" << count << "): ";
    int choice;
    std::cin >> choice;

    if (choice < 1 || choice > count)
    {
        std::cout << "Invalid choice. Nobody is selected.\n";
        return;
    }

    Entity* survivor = game->SafePlayers[candidates[choice - 1]];

    if (scenario == 0)
    {
        int damage = 3 + rand() % 8;
        survivor->TakeDamage(damage);
        survivor->DecreaseThirst(8);
        ConsoleColor::Print(survivor->GetName(), ConsoleColor::BRIGHT_CYAN);
        std::cout << " keeps watch and loses " << damage << " HP from exhaustion.\n";
    }
    else if (scenario == 1)
    {
        int repair = 25 + rand() % 21;
        game->house->RepairDoor(repair);
        survivor->DecreaseHunger(10);
        survivor->DecreaseThirst(10);
        ConsoleColor::Print(survivor->GetName(), ConsoleColor::BRIGHT_CYAN);
        std::cout << " repairs the door for +" << repair << " durability.\n";
    }
    else
    {
        if (rand() % 100 < 65)
        {
            int water = 1 + rand() % 2;
            game->world->GetWater()->AddQuantity(water);
            std::cout << "The trade is genuine. You receive +" << water << " water.\n";
        }
        else
        {
            int damage = 6 + rand() % 10;
            survivor->TakeDamage(damage);
            std::cout << "The trader was hostile. " << survivor->GetName()
                      << " escapes with " << damage << " damage.\n";
        }
    }
}
