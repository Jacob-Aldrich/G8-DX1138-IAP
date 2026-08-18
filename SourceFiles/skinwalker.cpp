#include "skinwalker.h"
#include <iostream>
#include <string>

void skinwalker::dialogue()
{
	displayImage();

	int randomiser = rand() % 3;
	setDialogue(randomiser);

	if (randomiser == 0)
	{
		std::cout << "PleAse hElp mE, I neeD sheltEr." << std::endl;
	}
	else if (randomiser == 1)
	{
		std::cout << "Hey, could you let me in? I've got some suplies to share." << std::endl;
	}
	else
	{
		std::cout << "...Young one... Let me in." << std::endl;
	}

}


void skinwalker::choiceDialogue()
{
	int choice = 0;

	while (choice != 1 && choice != 2)
	{
		std::cout << "What will you do?" << std::endl;
		std::cout << "1. Let them in" << std::endl;
		std::cout << "2. Don't let them in" << std::endl;
		std::cin >> choice;
	
	}

	if (choice == 1)
	{
		std::cout << "You let them in..." << std::endl;

		battle();
	}
	else
	{
		std::cout << "You refuse to let them in." << std::endl;
		std::cout << "How dare you!" << std::endl;
	}


}

void skinwalker::battle()
{
	int playerHealth = 100;
	int playerAttack = 20;
	int skinwalkerHealth = 50;
	int skinwalkerAttack = 15;
	int battlechoice = 0;

	while (playerHealth > 0 && skinwalkerHealth > 0)
	{
		std::cout << "Your Health: " << playerHealth << std::endl;
		std::cout << "Your Attack: " << playerAttack << std::endl;
		std::cout << "Skinwalker's Health: " << skinwalkerHealth << std::endl;

		std::cout << "What will you do?" << std::endl;
		std::cout << "1. Attack" << std::endl;
		std::cin >> battlechoice;
		if (battlechoice == 1)
		{
			skinwalkerHealth -= playerAttack;
			std::cout << "You attack the Skinwalker for " << playerAttack << " damage!" << std::endl;
			if (skinwalkerHealth > 0)
			{
				displayImage();
				playerHealth -= skinwalkerAttack;
				std::cout << "The Skinwalker attacks you for " << skinwalkerAttack << " damage!" << std::endl;
			}
		}
		
		else
		{
			std::cout << "Pick again." << std::endl;
		}

		if (playerHealth <= 0)
		{
			std::cout << "You have been defeated by the Skinwalker!" << std::endl;
		}
		else if (skinwalkerHealth <= 0)
		{
			std::cout << "You have defeated the Skinwalker!" << std::endl;
		}
	}
}

void skinwalker::wildbattle()
{
	int playerHealth = 100;
	int playerAttack = 20;
	int skinwalkerHealth = std::rand() % 25 + 30;
	int skinwalkerAttack = std::rand() % 5 + 15;
	int battlechoice = 0;

	while (playerHealth > 0 && skinwalkerHealth > 0)
	{
		std::cout << "Your Health: " << playerHealth << std::endl;
		std::cout << "Your Attack: " << playerAttack << std::endl;
		std::cout << "Skinwalker's Health: " << skinwalkerHealth << std::endl;

		displayImage();

		std::cout << "What will you do?" << std::endl;
		std::cout << "1. Attack" << std::endl;
		std::cout << "2. Run" << std::endl;
		std::cin >> battlechoice;
		if (battlechoice == 1)
		{
			skinwalkerHealth -= playerAttack;
			std::cout << "You attack the Skinwalker for " << playerAttack << " damage!" << std::endl;
			if (skinwalkerHealth > 0)
			{
				playerHealth -= skinwalkerAttack;
				std::cout << "The Skinwalker attacks you for " << skinwalkerAttack << " damage!" << std::endl;
			}
		}
		else if (battlechoice == 2)
		{
			int chance = std::rand() % 3; // 25% chance to escape
			if (chance == 0)
			{
				std::cout << "You successfully run away from the Skinwalker!" << std::endl;
				break;
			}
			else
			{
				std::cout << "You failed to run away!" << std::endl;
				playerHealth -= skinwalkerAttack;
				std::cout << "The Skinwalker attacks you for " << skinwalkerAttack << " damage!" << std::endl;
			}
			
		}
		else
		{
			std::cout << "Pick again." << std::endl;
		}

		if (playerHealth <= 0)
		{
			std::cout << "You have been defeated by the Skinwalker!" << std::endl;
		}
		else if (skinwalkerHealth <= 0)
		{
			std::cout << "You have defeated the Skinwalker!" << std::endl;
		}
	}
}

skinwalker::skinwalker() : Entity(50, 15) 
{
	imagechoice = rand() % 3; // Randomly choose an image
}

void skinwalker::displayImage()
{
	
	if (imagechoice == 0)
	{

		std::cout << R"(
@@@@@@@@@@@@@@@-++=+:@@@@+:-:@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@*==*+==-=--@*=+=----=@@@@@@@@@@@@@@@@
@@@@@@@@@@@-==**++=+==+++*+=+====%@@@@@@@@@@@@@@
@@@@@@@@@@====+==----==+=+-----==*+@@@@@@@@@@@@@
@@@@@@@@@-====+++==+=%=+++==+====++=@@@@@@@@@@@@
@@@@@@@@@#-===+=----@@@@*=-:---==+===@@@@@@@@@@@
@@@@@@@@@:====++==#@@@@@@@=-+====+=+-@@@@@@@@@@@
@@@@@@@@+=-======@@@@@@@@@@%=--==+==-+@@@@@@@@@@
@@@@@@@@:+-====+==--*@@**#+@=========+@@@@@@@@@@
@@@@@@@@:=-======--#@@@*===:=-======--@@@@@@@@@@
@@@@@@@=-+-=====+++.-@@**@+=+*=======-*@@@@@@@@@
@@@@@@@:-=-==:==@@@*-:#**+@@@@@@=====-#@@@@@@@@@
@@@@@@*+-*-=@+-=+=#@.+-=*@--+=+-=-==+-%@@@@@@@@@
@*+#%#+=:=-==*@=@@@*-@@@%*@@@@+=@*===-#@@@@@@@@@
@@@@@@*==@-+@@@@-:=+-@@@*=+-+==@@*==+=*@@@@@@@@@
@@@@@@*@@=++@@@@@=+#-@@@@@+=@@@@@@#==-#-=@@@@@@@
@@@@@@@+@%=-@@@@%@@#-@@@@@@@@@@@@@@++%#--**#%@+.
@@@@@@@@%#-@@@@@@+%#%@@#%#+%@@@@@@#=--+-@@@@@@@@
@@@@@@@==*.@@@@@=*@@@@@**@@@@@@@##==@.*@@@@@@@@@
@@@@@@@+::-@@@@@:@-%@@%@@#.%@@@-==+@@--@@@@@@@@@
@@@@@@@+%@=+@@@@@@=*@@@%%@#@@@@+%#+@@-*%@@@@@@@@
@@@@@@@@:+==+@@@@@@=@@=#@@@@@@@+@#+--:@@@@@@@@@@
@@@@@@@@:++=@%@@@@@+=+@@@@@@@@==@#=+=+#@@@@@@@@@
@@@@@@@@-:==@@@@@@=:-++##@@@@@#@@%==--#@@@@@@@@@
@@@@@@@:+++=+@@@@@@@+-*@@@@@@@@@@%=+=++@@@@@@@@@
@@@@@@@---==+@@@@@@@@@@@@@@@@@@@@%==----@@@@@@@@
@@@@%*+=+++==@@@@@@@@:*@@@@@@@@@@%++=++=@@@@@@@@
@@@##++---+==@@@@@@#+@@@@@@@@@@=#%++-=-+:@@@@@@@
@==**++=++==++%%@@@@@@@@@@@@:+++*#++=++==@@@@@@@
=++***+==-+=*+#++=@@@@@@@@.====*+#++==-+=*%@#+@@
@@=*#*+=++=++*%+=+++--*%%+-@++++*%++=++==%@@@@@@
@@@@@@@===++**%*@==@+%%##@@:=++**%*+==%+@@@@@@@@
@@@@@@@@@%@@@@@@@=#@@@@@@@@%++@@@@@=@@@@@@@@@@@@
@@@@@@@@@@@@@@@#*-++@@@@@@@+=+*@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@%@*++=+=@@@@+=++==@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@*+++**=%%#++++*@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@++++*#%%#++@@@@@@@@@@@**%@@@@@@
@@@@@@@@@@@@@@@@@@@**#%%%#*=@@@@@@@@@@@@@@@@@@@@
)";
	}
	else if (imagechoice == 1)
	{
		std::cout << R"(                                                                   
                                                                   
                           :.:.... -:::.                           
                    ..:..---::..::---::: :-:---                    
                   *-=-==%%#=+::==*%%++: :++###=                   
                   :  .. ::::.  .. :..:   :..::.:.                 
               . - --.-:-==-:-::-::=--:- -:----:-...               
                 %=#+:++*%@%++-=+=%%%#++ ++*%%%=+-.#.              
              .  :.:. ...:::......::::.. ..::::... :..             
                 :.--.-::==.--:-=:.=-:-- --::-..=::-:.             
              :. @.%--+=+%%:=+:*#=+@#**# ##**#--#*:=+.             
             ..: - #-:-=+-*=---:*--#+-== :+==#-:=::= +:            
                   .    -    .:::. ::.:  - .    ::. :-:            
               : :=   .      .  .=.#== .         =:%=:=            
              :- % := =  .   -.-.-% =: :   :. *  ..#*              
               :   =-:-      ::- .+.. := ==::=   :.=.-             
                 ...:.  .  . .  . ::.:...--:=:.. :.:.:             
               --*=.  - +. .:-    . ++.-.=*-+#: .=:-.+             
            . . -=:=:.. -=-. :       .-   -  -..:-.- -             
                : .:  ...  .        ... ..:.:: ... ...             
               : %**::- ## + :- -=+ -:=-.%*+###==-.%               
                 --- .-:-      . .==-.:. :-:==: =: :               
                             ...:  :..:: ::     :.                 
                   .:.   ..  -:.+=#*+**+ +.   . #                  
                   .::  .  = =.:: +.---- -:: :..                   
                      :.        :     :..::  :..                   
                      := - --*- +.-:+:**.=#=**                     
                      :.+ .- #:.%:%#++*=.*%+#%                     
                      . =...: :-. -=::-.  -::-                     
                      -    ..=:+=-.*=-+= -+.-                      
                        : #.+*-: +:%+=*- -#:                       
                        =. : : :+-.+=-=. -                         
                                                                   
 )";
	}
	else 
	{
		std::cout << R"(@@@@@--=:-#.=%+*-:*-#---#:=%::#*-=::%+#--=- *+*+:#+@@@@@
@@@@% ... . ........:.. ........... .........  ... %@@@@
@@@@%-=:%:-.--++---::--:-:*:#.=#=:-.#--:---.--++::-@@@@@
@@@@:...::=.#::::::=.::.:.==..-::::.:::::::-:..:...*@@@@
@@@@ :-=*::.----:--.---:-::--.:%+=#:=*#----:%==%+--+@@@@
%%%%   ..   .... .. .. .. ...  . .  ... ........ . -%%%%
@@@@ :-:-=*+%#@##@%*##-:==#+-:--===:%%#%%%#@%=-*.-:+@@@@
@@@@...::=. ....::... +...:=-..-. :.::::... .+.....%@@@@
@:-.@:.:- *. +=:    *+ .::---.: *    +:  .  -.-=::#:::#@
@-+:=. . .--   -# ++::- -:.=.     =*@% =% = :.   .:.:+@@
@.*.*=:.% :##    .:  :#.:=-=::-#    %%#=.+#.:#:-=%+=.=@@
%.++..--:.----:---:.:.-::.:. .:--.- -..----:::.:.--+#-@@
@  .:==.==. .::::==  ::.::--. .--...:=::-::::=.-:-:.  @@
@%%-*.::--:=-*#--=*=*=-.+-+-- .+-=+:**---++.#+.::-*%@@@@
@@@@ :#:-:-.---=:-::-- :+#%++.:=..-.:--:-=-:+-=+::#@@@@@
@@@@ :--.::.::-+:=-:::+  .:: .:*..:.:::::.::--::%@@@@@@@
%%%%%:::::-.--.....:-.::. :.-.:...: ....:.::-:=%%%%%%%%%
@@@@@@%%** =-+:::-:::-+-=.--+:+-==+.=--:=-= :%%@@@@@@@@@
@@@@@@@@+.+:::-::+--: ...--::.::. ::-:-----::@@@@@@@@@@@
@@@@@@@@@@:=**%::--:.%=        .=:: -*-:--:=@@@@@@@@@@@@
%%%%%%%%%%= ::-..:....----------..:.::-:::%%%%%%%%%%%%%%
@@@@@@@@@@@.##-=:-*:-----%*#=:-==-+.=#--: %@@@@@@@@@@@@@
@@@@@@@@@@@@%*:  . . =.... . ...     ....- @@@@@@@@@@@@@
@%%%%%%%%%%%%+:++:#. +...--:=:::=:+..%:=:+.%%%%%%%%%%%%%
@@@@@@@@@@@#++:..:= .- . .  =-:: .-..::::=- @@@@@@@@@@@@
%%%%%%%%%@-%%=*+==-...=- :  :.---:-:-=---=#::%%%%%%%%%%%
@@@@%%*+-....:.  ...  ...-=-:::. .. ......:. :--=%%@@@@@
..  =--+*:::=%=-=-:+=---+-+-:.+#::-:----:+*.%=-.:+-:....
)";
	}
}
