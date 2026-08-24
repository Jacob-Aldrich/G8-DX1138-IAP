#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Survivors.h"
#include "skinwalker.h"
#include "endings.h"

int main()
{

    srand(static_cast<unsigned int>(time(0)));

    std::cout << "=================================\n";
    std::cout << "       SKINWALKER SURVIVAL\n";
    std::cout << "=================================\n\n";

    Survivors survivors;
    skinwalker monster;

    int choice = 0;

    while (true)
    {
        std::cout << "\n========== MAIN MENU ==========\n";

        std::cout << "1. Look for a survivor\n";
        std::cout << "2. Send survivor scavenging\n";
        std::cout << "3. Encounter a stranger\n";
        std::cout << "4. Fight a wild Skinwalker\n";
        std::cout << "5. Eat / Drink\n";
        std::cout << "6. View status \n";
        std::cout << "7. Quit\n";

        std::cout << "\nChoose: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            survivors.dialogue();
            survivors.choiceDialogue();
            survivors.EndTurn();
            survivors.DisplayStatus();
            break;

        case 2:
            survivors.scavenging();
            survivors.EndTurn();
            survivors.DisplayStatus();
            break;

        case 3:
            monster.dialogue();
            monster.choiceDialogue();
            survivors.EndTurn();
            survivors.DisplayStatus();
            break;

        case 4:
            monster.wildbattle();
            survivors.EndTurn();
            survivors.DisplayStatus();
            break;

        case 5:
        {
            int foodChoice;

            std::cout << "\n========== FOOD & WATER ==========\n";
            std::cout << "1. Eat bread\n";
            std::cout << "2. Drink water\n";
            std::cout << "3. Use medical kit\n";
            std::cout << "4. Back\n";

            std::cout << "Choose: ";
            std::cin >> foodChoice;

            if (foodChoice == 1)
            {
                survivors.ConsumeBread();
            }
            else if (foodChoice == 2)
            {
                survivors.ConsumeWater();
            }
            else if (foodChoice == 3)
            {
                survivors.ConsumeMedicalKit();
            }

            break;
        }

        case 6:
            survivors.DisplayStatus();
            survivors.EndTurn();
            break;


        case 7:
            std::cout << "Goodbye!\n";
            return 0;

        default:
            std::cout << "Invalid choice.\n";
            break;
        }
    }

    return 0;
}
