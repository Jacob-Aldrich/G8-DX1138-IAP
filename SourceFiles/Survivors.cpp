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
	int randomiser = rand() % 10;
	setDialogue(randomiser);

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
        std::cout << "???: 'May I be let in? I don't have much.'" << std::endl;
    }
    else if (randomiser == 3)
    {
        std::cout << "???: 'Hey! Let me in right now!'" << std::endl;
    }
    else if (randomiser == 4)
    {
        std::cout << "???: 'Open up! I need shelter!'" << std::endl;
    }
    else if (randomiser == 5)
    {
        std::cout << "???: 'You look like you're living peacefully! Share some with me will you?'" << std::endl;
    }
    else if (randomiser == 6)
    {
        std::cout << "???: 'I have supplies!'" << std::endl;
    }
    else if (randomiser == 7)
    {
        std::cout << "???: 'Have you heard about the news lately? Well I have, let me in and I'll tell you!'" << std::endl;
    }
    else if (randomiser == 8)
    {
        std::cout << "???: 'I have some spare supplies. Your shelther for my supplies, how's that sound?'" << std::endl;
    }
	else
	{
		std::cout << "???: 'I have information about a safe house!'" << std::endl;
	}

}

void Survivors::setDialogue(int randomiser)
{
    // 
}

int Survivors::GetNoOfSurvivors() const
{
    return NoOfSurvivors;
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
            int choice;

            std::cout << "You currently have "
                << NoOfSurvivors
                << " survivor(s)." << std::endl;

            std::cout << "Would you like to send a survivor to scavenge?"
                << std::endl;

            std::cout << "1. Yes" << std::endl;
            std::cout << "2. No" << std::endl;

            std::cin >> choice;

            if (choice == 1)
            {
                std::cout << "A survivor has gone scavenging..."
                    << std::endl;

                NoOfSurvivors--;

                // Scavenging happens here
            }
        }
        else
        {
            std::cout << "You have an insufficient amount of people."
                << std::endl;
        }
    
}


Survivors::Survivors() : Entity(70, 10)
{
    NoOfSurvivors = 0;
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

    std::cout << "Survivors: " << NoOfSurvivors << std::endl;
    std::cout << "Hunger: " << Hunger << "/100" << std::endl;
    std::cout << "Thirst: " << Thirst << "/100" << std::endl;

    std::cout << "=====================================\n";
}

void Survivors::EndTurn()
{
    ReduceHunger(10);
    ReduceThirst(15);

    std::cout << "\nTime passes...\n";

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



