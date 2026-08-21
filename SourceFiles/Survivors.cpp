#include "Survivors.h"
#include "endings.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

void Survivors::dialogue()
{
    imagechoice = rand() % 4;
	displayImage();

	// put this is main pls ---> srand(static_cast<unsigned int>(time(0)));
	int randomiser = rand() % 3;
	setDialogue(randomiser);

	if (randomiser == 0)
	{
		std::cout << "???: 'Please let me in, I'll help the best of my ability!'" << std::endl;
	}
	else if (randomiser == 1)
	{
		std::cout << "???: 'I have supplies!'" << std::endl;
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
