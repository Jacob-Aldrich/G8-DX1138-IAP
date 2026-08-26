#include "Survivors.h"
#include "endings.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

void Survivors::dialogue()
{
    imagechoice = rand() % 3;
	displayImage();

	// put this is main pls ---> srand(static_cast<unsigned int>(time(0)));
	int randomiser = rand() % 4;

    CurrentSurvivorType = rand() % 3;

	setDialogue(randomiser);

	
}

void Survivors::setDialogue(int randomiser)
{
    if (CurrentSurvivorType == 0)
    {
        if (randomiser == 0)
        {
            std::cout << "???: 'Please let me in, I'll help to the best of my ability!'" << std::endl;
        }
        else if (randomiser == 1)
        {
            std::cout << "???: 'Can I come in? I can help!'" << std::endl;
        }
        else if (randomiser == 2)
        {
            std::cout << "???: 'I have some spare supplies. We could help each other.'" << std::endl;
        }
        else 
        {
            std::cout << "???: 'May I be let in? I don't have much.'" << std::endl;
        }
    }
    else if (CurrentSurvivorType == 1)
    {
        if (randomiser == 0)
        {
            std::cout << "???: 'Hey! Let me in right now!'" << std::endl;
        }
        else if (randomiser == 1)
        {
            std::cout << "???: 'Open up! I need shelter!'" << std::endl;
        }
        else if (randomiser == 2)
        {
            std::cout << "???: 'You've got supplies in there. Don't pretend you don't.'" << std::endl;
        }
        else
        {
            std::cout << "???: 'You look like you're living peacefully! Share some with me will you?'" << std::endl;
        }
    }
    else
    {
        if (randomiser == 0)
        {
            std::cout << "???: 'I have supplies!'" << std::endl;
        }
        else if (randomiser == 1)
        {
            std::cout << "???: 'Have you heard about the news lately? Well I have, let me in and I'll tell you!'" << std::endl;
        }
        else if (randomiser == 2)
        {
            std::cout << "???: 'I have some spare supplies. Your shelther for my supplies, how's that sound?'" << std::endl;
        }
        else
        {
            std::cout << "???: 'I have information about a safe house!'" << std::endl;
        }
    }
}

int Survivors::GetNoOfSurvivors() const
{
    return NoOfSurvivors;
}

//void Survivors::AddRandomSurvivor()
//{
//    int type = rand() % 3;
//
//    if (type == 0)
//    {
//        KindCount++;
//        KindSurvivor();
//    }
//    else if (type == 1)
//    {
//        MeanCount++;
//        MeanSurvivor();
//    }
//    else
//    {
//        ResourcefulCount++;
//        ResourcefulSurvivor();
//    }
//}

int Survivors::GetKindCount() const
{
    return KindCount;
}

int Survivors::GetMeanCount() const
{
    return MeanCount;
}

int Survivors::GetResourcefulCount() const
{
    return ResourcefulCount;
}

void Survivors::choiceDialogue() 
{
	int choice = 0;

	while (choice != 1 && choice != 2 && choice!= 3)
	{
		std::cout << "What will you do?" << std::endl;
        std::cout << "1. Attack" << std::endl;
        std::cout << "2. Reject them" << std::endl;
		std::cout << "3. Let them in" << std::endl;
		std::cin >> choice;

	}

    if (choice == 1)
    {
        std::cout << "You injured an innocent. They no longer want to work with you  " << std::endl;
    }

    else if (choice == 2)
    {
        std::cout << "You refuse to let them in." << std::endl;
        std::cout << "???: 'How dare you!'" << std::endl;
    }

	else if (choice == 3)
	{
        std::cout << "You let them in..." << std::endl;

        NoOfSurvivors++;

        if (CurrentSurvivorType == 0)
        {
            KindCount++;
            std::cout << "They are a Kind Survivor." << std::endl;
        }
        else if (CurrentSurvivorType == 1)
        {
            MeanCount++;
            std::cout << "They are a Mean Survivor." << std::endl;
        }
        else
        {
            ResourcefulCount++;
            std::cout << "They are a Resourceful Survivor." << std::endl;
        }

        std::cout << "Survivors: " << NoOfSurvivors << std::endl;
    }
	else
	{
		std::cout << "..." << std::endl;
	}


}

void Survivors::scavenging()
{

    if (NoOfSurvivors > 0)
    {
        if (NoOfSurvivors <= 0)
        {
            std::cout << "You have an insufficient amount of people.\n";
            return;
        }

        std::cout << "\n========== SCAVENGING ==========\n";

        std::cout << "Kind survivors: "
            << KindCount << std::endl;

        std::cout << "Mean survivors: "
            << MeanCount << std::endl;

        std::cout << "Resourceful survivors: "
            << ResourcefulCount << std::endl;

        std::cout << "\nWho do you want to send?\n";

        std::cout << "1. Kind survivor\n";
        std::cout << "2. Mean survivor\n";
        std::cout << "3. Resourceful survivor\n";
        std::cout << "4. Cancel\n";

        int choice;
        std::cin >> choice;

        if (choice == 1)
        {
            if (KindCount <= 0)
            {
                std::cout << "You don't have a Kind survivor.\n";
                return;
            }

            KindCount--;

            int suppliesFound = 3;

            std::cout << "The Kind survivor went scavenging.\n";
            int supplies = rand() % 4 + 4;

            std::cout << "They returned with "
                << supplies
                << " supplies!\n";
          
        }

        else if (choice == 2)
        {
            if (MeanCount <= 0)
            {
                std::cout << "You don't have a Mean survivor.\n";
                return;
            }

            MeanCount--;

            int suppliesFound = 1;

            std::cout << "The Mean survivor went scavenging.\n";
            int supplies = rand() % 4 + 4;

            std::cout << "They returned with "
                << supplies
                << " supplies!\n";
        
        }

        else if (choice == 3)
        {
            if (ResourcefulCount <= 0)
            {
                std::cout << "You don't have a Resourceful survivor.\n";
                return;
            }

            ResourcefulCount--;

            int suppliesFound = 4;

            std::cout << "The Resourceful survivor went scavenging.\n";
            int supplies = rand() % 4 + 4;

            std::cout << "They returned with "
                << supplies
                << " supplies!\n";
        }

        else if (choice == 4)
        {
            std::cout << "You cancelled scavenging.\n";
        }
    }
}


Survivors::Survivors() : Entity(70, 10)
{
    NoOfSurvivors = 0;

    KindCount = 0;
    MeanCount = 0;
    ResourcefulCount = 0;

    Hunger = 100;
    Thirst = 100;

    breadCount = 3;
    waterCount = 3;
    medicalKitCount = 2;
}

void Survivors::SetHunger(int value) {
    Hunger = (value > 100 ? 100 : (value < 0 ? 0 : value));
}
void Survivors::SetThirst(int value) {
    Thirst = (value > 100 ? 100 : (value < 0 ? 0 : value));
}
int Survivors::GetHunger() const {
    return Hunger;
}

int Survivors::GetThirst() const {
    return Thirst;
}

void Survivors::ReduceHunger(int amount)
{
    Hunger -= amount;
    if (Hunger < 0)
    {
        Hunger = 0;
    }
}

void Survivors::ReduceThirst(int amount)
{
    Thirst -= amount;
    if (Thirst < 0)
    {
        Thirst = 0;
    }
}

void Survivors::DisplayStatus() const
{
    if (NoOfSurvivors <= 0)
    {
        return;
    }

    std::cout << "\n========== SURVIVOR STATUS ==========\n";

    std::cout << "Total Survivors: "
        << NoOfSurvivors << std::endl;

    std::cout << "Kind Survivors: "
        << KindCount << std::endl;

    std::cout << "Mean Survivors: "
        << MeanCount << std::endl;

    std::cout << "Resourceful Survivors: "
        << ResourcefulCount << std::endl;

    std::cout << "Hunger: "
        << Hunger << "/100" << std::endl;

    std::cout << "Thirst: "
        << Thirst << "/100" << std::endl;

    std::cout << "=====================================\n";
}

void Survivors::EndTurn()
{
    if (NoOfSurvivors <= 0)
    {
        return;
    }

    int hungerLoss = 0;
    int thirstLoss = 0;

    // Kind survivors consume less
    hungerLoss += KindCount * 5;
    thirstLoss += KindCount * 8;

    // Mean survivors consume more
    hungerLoss += MeanCount * 15;
    thirstLoss += MeanCount * 20;

    // Resourceful survivors consume normal amounts
    hungerLoss += ResourcefulCount * 10;
    thirstLoss += ResourcefulCount * 15;

    ReduceHunger(hungerLoss);
    ReduceThirst(thirstLoss);

    std::cout << "\nTime passes...\n";

    std::cout << "Hunger -" << hungerLoss << std::endl;
    std::cout << "Thirst -" << thirstLoss << std::endl;

    if (Hunger <= 0)
    {
        std::cout << "Your survivors are starving!\n";
    }

    if (Thirst <= 0)
    {
        std::cout << "Your survivors are dehydrated!\n";
    }
}

void Survivors::ConsumeBread()
{
    if (breadCount <= 0)
    {
        std::cout << "No Bread left!\n";
        return;
    }

    if (Hunger >= 100)
    {
        std::cout << "They are already full!\n";
        return;
    }

    breadCount--;

    Hunger += 20;

    if (Hunger > 100)
    {
        Hunger = 100;
    }

    std::cout << "Survivor ate some bread.\n";
    std::cout << "Hunger: " << Hunger << "/100\n";
    std::cout << "Bread remaining: " << breadCount << "\n";
}

void Survivors::ConsumeWater()
{
    if (waterCount <= 0)
    {
        std::cout << "No water left!\n";
        return;
    }

    if (Thirst >= 100)
    {
        std::cout << "Survivor is not thirsty!\n";
        return;
    }

    waterCount--;

    Thirst += 20;

    if (Thirst > 100)
    {
        Thirst = 100;
    }

    std::cout << "Survivor drank some water.\n";
    std::cout << "Thirst: " << Thirst << "/100\n";
    std::cout << "Water remaining: " << waterCount << "\n";
}

void Survivors::ConsumeMedicalKit() {
    if (medicalKitCount <= 0)
    {
        std::cout << "No MedicalKits left!\n";
        return;
    }

    if (SHealthPoints >= 70)
    {
        std::cout << "Survivor is not hurt!\n";
        return;
    }

    medicalKitCount--;

    SHealthPoints += 20;

    if (SHealthPoints > 70)
    {
        SHealthPoints = 70;
    }
    
    if (SHealthPoints < 0)
    {
        SHealthPoints = 0;
    }

    std::cout << "Survivor Healed up.\n";
    std::cout << "HP: " << SHealthPoints << "\n";
    std::cout << "MedicalKits remaining: " << medicalKitCount << "\n";
}


void Survivors::displayImage() const
{

	if (imagechoice == 0)
	{

		std::cout << R"(
				   +#######+              
               #+-...........-+                  
             #+.................+#             
       #+## #-......---..+--.....-+         
       #+-##+......-. ...  ..-....-#      
           +-......   ...   ..-...-+      
         ++-......   ...    .. ...-+       
        +-..----..   ..    .-. ..--.+     
        #-..-- -..-++-   . ....-.-..-     
         #-.-- . .---.... .++--.-..-#     
        +-..-+++-    .        .---.-       
         #-..--+++-..       .---..-+          
          -..---######---#####+---+  +#     
          +-..--####+-+..++###+..-#+ ++       
          +-.---##########+-+##--+  ++           
           +----+##############++                      
           --++++++++++++++++++--
)";
	}
	else if (imagechoice == 1)
	{
		std::cout << R"(    
..     .            ..                             
                ....--+-.........--.--+-...--                          
               ...-+...--+---+-++--++-..-+-..-.                        
              ...-.---+---+--+-+--+-..-----+---                        
              .-----+---+-         -+..-+---+--.                       
             .-----+---+.           .+-.-+--++--.                      
            ...-+-----+.              +..-+-++--.                      
            .-.-+++---..-.          ...+.-+++-.--.                     
           ...--+++-+###+-.       .++###+--#+--.--                     
           ...--. --+ .+###-     .+-##- +--- .-.--.                    
          .-.---. --+.  ..         ... .---. ------                    
          .----+--+-+.        .        .+-+--+-----.                   
          .+--++---+++-.              -+++-.-+-----.                   
          .+--+++--+++++---++-..++++.+++++--++---+-.                   
          .-+++++++++++#- -+------+ .#++++++++---+-                    
            -+-+++++++#- ----------+ .++++++++--+-                     
              -++++++-+##+--.---..-+###-+++++--+.                      
               .+++++++-+-----+-....+--#++++++.                        
                  .+++.-++---+.-----++.++++-                           
                    .. +#####-  ######.  -                             
                        .-...    .--.                                                               
                                                                   
                                     
                                                                   
 )";
	}
	else
	{
		std::cout << R"(
                                 ....--.                                 
                         ++-  .........---++.                            
                        - .++..........+##+-+#++++-                      
                       .+###+.............+----++++-                     
                      +#++---...-........--+++++++##                      
                     -###++-+#-........--++++#+++###                     
                    .########+-----. .----+####++###-                    
                    .#####  +-++-----------+#########                    
                    .##- .+############++++++++++####                    
                    ++.########+++-+###++###+++++####+-+-                
                   .+#########-#++---++-++#+++###+#++#.                  
                  -###+###++#++- --++--+.-+--+#--+-+#+..                 
                 +####-+++--+++++.--... .++#+++-+--++###-                
                #######-++-++-+-.-   .- .+---+--+###+ .-                 
                  ####--###-.              ..-+++-###+                   
                   .#####-.--..          . ..--.-+                       
                      -.+#####.          . .####                         
                  .## .#+--+#####+      -###########.# .-                       
                   +##.##+---#+..+#+++-+#####+##..###-+.                 
                   +#+####++###+##++##########+######-.                  
                  ###########+#+  ...########+#########.                 
                 + -++#++##+ .---....###+###########+##.                 
                ### #++###--++#++++++#####..+######+####.                
                .##.##+#.+#++++#+++###+##+. .++++#######.                
                    ++# -#+++++++++######++-++++++####                   
                      -####++####+########++++#+++#-                     
                         .-+##############+####-.                        
                                   ###+.

)";
	}
}



