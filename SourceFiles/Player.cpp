#include "Player.h"
#include <iostream>
#include <string>

Player::Player() : Entity(100, 20) // Initialize base class with health and attack points
{
	Look0 = R"(                                                      
          _   ____  _.-"-._
        .' `;'    ':.      '-.
       /  ./     .'`\`-...-'`
      /  /|D_  .O    |
     /  / |=\/`=     |
    |_.'  |  |       |
           \  \   _ /_
           /`---'}_()_{
          /`'---' //\\\
         /;      (/\ \)\
        / |         \   \
       /  |         |   |
      /  / .     _ /   /
      \_|   '. .'  '-'|
        \    .-|     /
     _.-'   /  |    /
    (      /  / .--;
     '-.__/   |    /
              \__.
)"; // Default look for the player

	Look1 = R"(
			  .-.
			 (o.o)
			  |=|
			 __|__
		   //.=|=.\\
		  // .=|=. \\
		  \\ .=|=. //
		   \\(_=_)//
			(:| |:)
			 || ||
			 () ()
			 || ||
			 || ||
			==' '==
)";
	Look2 = R"(
   ,^~~~-.         .-~~~"-.
  :  .--. \       /  .--.  \
  : (    .-`<^~~~-: :    )  :
  `. `-,~            ^- '  .'
    `-:                ,.-~
      .'                  `.
     ,'   @   @            |
     :    __               ;
  ...{   (__)          ,----.
 /   `.              ,' ,--. `.
|      `.,___   ,      :    : :
|     .'    ~~~~       \    / :
 \.. /               `. `--' .'
    |                  ~----~
    |                      |
     ----------------------
)";
	Look3 = R"(
         .--.. .--..                         
        / #  \/ # \ \                    
       |# # #|# # #| \                  
      ,:  ___; ___ |  |           
    ,~   /   \/   \    ~`.           
   .,--.|    |     | ,.. #`.           
   :    |  * | *   |'   `. #:        
  |`.    \___/\___/      ;  :          
  :  ~|     ( )       /~    #           
  `#   \    /~\      /     |'            
   `.   `--'   `----'    #/               
     \#                  .'               
      `-..             #/.                  
      /#  ~          ~~  #\
)";
	Look4 = R"(
          ..  .-~~~-. ..                  
     .--.'  `'       '  ;.                   
   .'                     `,                  
   `. ,.'`.__'~-.           :               
     ~ /~  / ~\  `-       .,'
      |___|____| :          `.
      |  *| *  |  `-.        ;            
       \__/\__/      ~;     |'         
      /  `.           `-...;'         
      |   |                ;       
      |   ;                |             
      `.  `._              |         
        \   ~~~           .'              
         `.__________.'   :              
                `
)";

	Dialogue1 = "\"It's been a while\"";
	Dialogue2 = "\"Who are you?\"";
	Dialogue3 = "\"No!\"";
}

void Player::Speak(int choice)
{
	switch (choice) {
	case 1:
		std::cout << Dialogue1 << std::endl;
		break;
	case 2:
		std::cout << Dialogue2 << std::endl;
		break;
	case 3:
		std::cout << Dialogue3 << std::endl;
		break;
	default:
		std::cout << "..." << std::endl;
		break;
	}
}

std::string Player::GetLook0() {
	return Look0;
}

std::string Player::GetLook1()
{
	return Look1;
}

std::string Player::GetLook2()
{
	return Look2;
}

std::string Player::GetLook3()
{
	return Look3;
}

std::string Player::GetLook4()
{
	return Look4;
}

void Player::SkinWalkerAtDoor(int choice)
{

	bool skinwalkerAtDoor = false;

	if (skinwalkerAtDoor) {
		switch (choice) {
		case 1:
			std::cout << "Let them in" << std::endl;
			break;
		case 2:
			std::cout << "Don't let them in" << std::endl;
			break;
		default:
			std::cout << "..." << std::endl;
			break;
		}
	}
}

void Player::EncounterSkinwalker(int choice)
{
	bool encounteredskinwalker = false;

	if (encounteredskinwalker) {
		switch (choice) {
		case 1:
			std::cout << "Battle" << std::endl;
			break;
		default:
			std::cout << "..." << std::endl;
			break;
		}
	}
	
}

bool Player::SkinwalkerAtDoor()
{
	// Currently always returns false; update logic later if needed
	bool skinwalkerAtDoor = false;
	return skinwalkerAtDoor;
}

bool Player::EncounterSkinwalker() {
	bool EncounteredSkinwalker = false;
	return EncounteredSkinwalker;
}


void Player::SurvivorsAtDoor(int choice)
{

	bool survivorsAtDoor = false;

	if (survivorsAtDoor) {
		switch (choice) {
		case 1:
			std::cout << "Let them in" << std::endl;
			break;
		case 2:
			std::cout << "Don't let them in" << std::endl;
			break;
		default:
			std::cout << "..." << std::endl;
			break;
		}
	}
}

//void Player::EncounterSurvivors(int choice)
//{
//	bool encounteredsurvivors = false;
//
//	if (encounteredsurvivors) {
//		switch (choice) {
//		case 1:
//			std::cout << "Battle" << std::endl;
//			break;
//		default:
//			std::cout << "..." << std::endl;
//			break;
//		}
//	}
//
//}

bool Player::SurvivorsAtDoor()
{
	// Currently always returns false; update logic later if needed
	bool survivorsAtDoor = false;
	return survivorsAtDoor;
}

//bool Player::EncounterSurvivors() {
//	bool EncounteredSurvivors = false;
//	return EncounteredSurvivors;
//}
