#include "skinwalker.h"
#include "endings.h"
#include <iostream>
#include <string>

void skinwalker::dialogue()
{
	displayImage();

	srand(static_cast<unsigned int>(time(0)));
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
		std::cout << "1. Attack" << std::endl;
		std::cout << "2. Reject them" << std::endl;
		std::cout << "3. Let them in" << std::endl;
		std::cin >> choice;
	
	}

	if (choice == 1)
	{
		std::cout << "You attacked them! " << std::endl;
		battle();
	}
	else if (choice == 2)
	{
		std::cout << "You refuse to let them in." << std::endl;
		std::cout << "How dare you!" << std::endl;
	}

	else if (choice == 3)
	{
		std::cout << "You let them in..." << std::endl;

		battle();
	}

	else
	{
		std::cout << "..." << std::endl;
	}

}

void skinwalker::battle() const
{
	int PHealthPoints = 100;
	int PAttackpoints = 20;
	int skinwalkerHealth = 50;
	int skinwalkerAttack = 15;
	int battlechoice = 0;

	while (PHealthPoints > 0 && skinwalkerHealth > 0)
	{
		std::cout << "Your Health: " << PHealthPoints << std::endl;
		std::cout << "Your Attack: " << PAttackpoints << std::endl;
		std::cout << "Skinwalker's Health: " << skinwalkerHealth << std::endl;

		std::cout << "What will you do?" << std::endl;
		std::cout << "1. Attack" << std::endl;
		std::cin >> battlechoice;
		if (battlechoice == 1)
		{
			int SWNewHP = skinwalkerHealth - PAttackpoints;
			std::cout << "You attack the Skinwalker for " << PAttackpoints << " damage!" << std::endl;
			std::cout << "Skinwalker has" << SWNewHP << " HP left!" << std::endl;;
			if (SWNewHP > 0)
			{
				displayImage();
				int PnewHP = PHealthPoints - skinwalkerAttack;
				std::cout << "The Skinwalker attacks you for " << skinwalkerAttack << " damage!" << std::endl;
				std::cout << "You have" << PnewHP << " HP left!" << std::endl;
			}
		}
		
		else
		{
			std::cout << "Pick again." << std::endl;
		}

		if (PHealthPoints <= 0)
		{
			std::cout << "You have been defeated by the Skinwalker!" << std::endl;
			endings ending;
			ending.DeathEnding();

			return;
		}
		else if (skinwalkerHealth <= 0)
		{
			std::cout << "You have defeated the Skinwalker!" << std::endl;
		}
	}
}

void skinwalker::wildbattle() const
{

	srand(static_cast<unsigned int>(time(0)));
	int PHealthPoints = 100;
	int PAttackpoints = 20;
	int skinwalkerHealth = std::rand() % 25 + 30;
	int skinwalkerAttack = std::rand() % 5 + 15;
	int battlechoice = 0;

	while (PHealthPoints > 0 && skinwalkerHealth > 0)
	{
		std::cout << "Your Health: " << PHealthPoints << std::endl;
		std::cout << "Your Attack: " << PAttackpoints << std::endl;
		std::cout << "Skinwalker's Health: " << skinwalkerHealth << std::endl;

		displayImage();

		std::cout << "What will you do?" << std::endl;
		std::cout << "1. Attack" << std::endl;
		std::cout << "2. Run" << std::endl;
		std::cin >> battlechoice;
		if (battlechoice == 1)
		{
			int SWNewHP = skinwalkerHealth - PAttackpoints;
			std::cout << "You attack the Skinwalker for " << PAttackpoints << " damage!" << std::endl;
			std::cout << "Skinwalker has" << SWNewHP << " HP left!" << std::endl;;
			if (SWNewHP > 0)
			{
				displayImage();
				int PnewHP = PHealthPoints - skinwalkerAttack;
				std::cout << "The Skinwalker attacks you for " << skinwalkerAttack << " damage!" << std::endl;
				std::cout << "You have" << PnewHP << " HP left!" << std::endl;
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
				displayImage();
				int PnewHP = PHealthPoints - skinwalkerAttack;
				std::cout << "The Skinwalker attacks you for " << skinwalkerAttack << " damage!" << std::endl;
				std::cout << "You have" << PnewHP << " HP left!" << std::endl;
			}
			
		}
		else
		{
			std::cout << "Pick again." << std::endl;
		}

		if (PHealthPoints <= 0)
		{
			std::cout << "You have been defeated by the Skinwalker!" << std::endl;
			endings ending;
			ending.DeathEnding();

			return;
		}
		else if (skinwalkerHealth <= 0)
		{
			std::cout << "You have defeated the Skinwalker!" << std::endl;
		}
	}
}

skinwalker::skinwalker() : Entity(50, 15) 
{
	srand(static_cast<unsigned int>(time(0)));
	imagechoice = rand() % 3; // Randomly choose an image
}

void skinwalker::displayImage() const
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
		std::cout << R"(
@@@@@--=:-#.=%+*-:*-#---#:=%::#*-=::%+#--=- *+*+:#+@@@@@
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
