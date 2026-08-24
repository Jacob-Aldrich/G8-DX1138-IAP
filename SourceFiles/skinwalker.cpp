#include "skinwalker.h"
#include "endings.h"
#include <iostream>
#include <cstdlib>
#include <ctime>


void skinwalker::dialogue()
{
	imagechoice = rand() % 4;
	displayImage();

	int randomiser = rand() % 5;
	setDialogue(randomiser);

	if (randomiser == 0)
	{
		std::cout << "???: 'PleAse hElp mE, I neeD sheltEr.'" << std::endl;
	}
	else if (randomiser == 1)
	{
		std::cout << "???: 'Hey, could you let me in? I've got some suplies to share.'" << std::endl;
	}
	else if (randomiser == 2)
	{
		std::cout << "???: 'I have some lnformation to share! Please let me in!'" << std::endl;
	}
	else if (randomiser == 3)
	{
		std::cout << "???: 'Can I come in...?'" << std::endl;
	}
	else
	{
		std::cout << "???: '...Young one... Let me in.'" << std::endl;
	}

}

void skinwalker::setDialogue(int randomiser)
{
	//
}


void skinwalker::choiceDialogue()
{
	int choice = 0;

	while (choice != 1 && choice != 2 && choice !=3)
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
		std::cout << "???: 'How dare you!'" << std::endl;
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
	int PAttackPoints = 20;

	int skinwalkerHealth = 50;
	int skinwalkerAttack = 15;

	int battleChoice = 0;

	int turn = 1;

	while (PHealthPoints > 0 && skinwalkerHealth > 0)
	{

		std::cout << "========== TURN " << turn << " ==========" << std::endl;
		std::cout << "\033[32mYour HP: \033[0m" << PHealthPoints << std::endl; //green
		std::cout << "Skinwalker's HP: " << skinwalkerHealth << std::endl;

		displayImage();


		std::cout << "What will you do?" << std::endl;
		std::cout << "1. Attack" << std::endl;
		std::cout << "2. Item" << std::endl;

		std::cin >> battleChoice;



		if (battleChoice == 1)
		{
			skinwalkerHealth -= PAttackPoints;

			std::cout << "You attack the Skinwalker for" << std::endl
				<< PAttackPoints
				<< " damage!" << std::endl;

			if (PAttackPoints > 30)
			{
				std::cout << "\033[36mIt was super effective!\033[0m" << std::endl; //cyan
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

			/*  Can put the ACTUAL items here later */
		}


		else
		{
			std::cout << "Pick a valid option." << std::endl;
			continue;
		}


		if (skinwalkerHealth <= 0)
		{
			std::cout << "\033[36mYou have defeated the Skinwalker\033[0m!" << std::endl;

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
			std::cout << "\033[36mIt was super effective!\033[0m" << std::endl; //cyan
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

		std::cout << "\033[32mYour HP: \033[0m" //green
			<< PHealthPoints
			<< std::endl;


		if (PHealthPoints <= 0)
		{
			std::cout << "\033[31mYou have been defeated by the Skinwalker!\033[0m" << std::endl; //making the text red

			endings ending;
			ending.DeathEnding();

			return;
		}
		turn++;
	}
}


void skinwalker::wildbattle() const
{

	int PHealthPoints = 100;
	int PAttackpoints = 20;
	int skinwalkerHealth = std::rand() % 25 + 30;
	int skinwalkerAttack = std::rand() % 5 + 15;
	int battlechoice = 0;

	int Turns = 1;

	while (PHealthPoints > 0 && skinwalkerHealth > 0)
	{
		

		std::cout << "========== TURN " << Turns << " ==========" << std::endl;
		std::cout << "\033[32mYour HP: \033[0m" << PHealthPoints << std::endl; //green
		std::cout << "Your Attack: " << PAttackpoints << std::endl;
		std::cout << "Skinwalker's HP: " << skinwalkerHealth << std::endl;
		
		

		displayImage();

		std::cout << "What will you do?" << std::endl;
		std::cout << "1. Attack" << std::endl;
		std::cout << "2. Item" << std::endl;
		std::cout << "3. Run" << std::endl;

		std::cin >> battlechoice;

		if (battlechoice == 1)
		{
			skinwalkerHealth -= PAttackpoints;

			std::cout << "You attack the Skinwalker for" << std::endl
				<< PAttackpoints
				<< " damage!" << std::endl;

			if (PAttackpoints > 30)
			{
				std::cout << "\033[36mIt was super effective!\033[0m" << std::endl; //cyan
			}

			else if (PAttackpoints < 10)
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


		else if (battlechoice == 2)
		{
			std::cout << "You used an item!" << std::endl;

			/*  Can put the ACTUAL items here later
			*/
		}

		else if (battlechoice == 3)
		{
			int chance = std::rand() % 4; //25% chance to escape

			if (chance == 0)
			{
				std::cout << "\033[36mYou escaped from the Skinwalker!\033[0m" << std::endl; //cyan
				return;
			}
			else
			{
				std::cout << "\033[31mYou failed to escape!\033[0m" << std::endl; //red
			}
		}

		else
		{
			std::cout << "Pick a valid option." << std::endl;
			continue;
		}


		if (skinwalkerHealth <= 0)
		{
			std::cout << "\033[36mYou have defeated the Skinwalker\033[0m!" << std::endl;

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
			std::cout << "\033[36mIt was super effective!\033[0m" << std::endl; //cyan
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

		std::cout << "\033[32mYour HP: \033[0m" //green
			<< PHealthPoints
			<< std::endl;


		if (PHealthPoints <= 0)
		{
			std::cout << "\033[31mYou have been defeated by the Skinwalker!\033[0m" << std::endl; //making the text red

			endings ending;
			ending.DeathEnding();

			return;
		}
		Turns++;
	}
}


skinwalker::skinwalker() : Entity(50, 15) 
{
	
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

	else if (imagechoice == 2)
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
