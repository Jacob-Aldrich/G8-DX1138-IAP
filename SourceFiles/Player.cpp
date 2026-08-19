#include "Player.h"
//#include "skinwalker.h"
#include <iostream>
#include <string>

Player::Player() : Entity(100, 20) // Initialize base class with health and attack points
{	// Default look for the player
	Look0 = "\033[38;2;174;198;207m" + std::string(R"(
       ,__,.........     
     /''          '\\    
    /                \   
   /     `.     `.   \   
  /    ,' '-b`,-'\_   \  
  |  _/'  o  ' o  ',- |  
  /  ' |          |'  \  
 /     '-........-'    \ 
 |       |      |       | 
 |       /      \       | 
-+     /-\      /-\     +-
  \---/   \----/   \---/  

)") + "\033[0m"; 
	//angry
	Look1 = "\033[38;2;137;171;191m" + std::string(R"(
       ,__,.........     
     /''          '\\    
    /                \   
   /     `.     `.   \   
  /    ,' '-b`,-'\_   \  
  |  _/' ,\  '/,  ',- |  
  /  ' |  '   '   |'  \  
 /     '-........-'    \ 
 |       |      |       | 
 |       /      \       | 
-+     /-\      /-\     +-
  \---/   \----/   \---/  
)") + "\033[0m";
	//crying
	Look2 = "\033[38;2;174;198;207m" + std::string(R"(
       ,__,.........     
     /''          '\\    
    /                \   
   /     `.     `.   \   
  /    ,' '-b`,-'\_   \  
  |  _/'  __' __  ',- |  
  /  ' |  |    |  |'  \  
 /     '-........-'    \ 
 |       |      |       | 
 |       /      \       | 
-+     /-\      /-\     +-
  \---/   \----/   \---/  
)") + "\033[0m";
	//shocked
	Look3 = "\033[38;2;150;168;220m" + std::string(R"(
       ,__,.........     
     /''          '\\    
    /                \   
   /     `.     `.   \   
  /    ,' '-b`,-'\_   \  
  |  _/' ,_  '_.  ',- |  
  /  ' | ()   ()  |'  \  
 /     '-.. O ...-'    \ 
 |       |      |       | 
 |       /      \       | 
-+     /-\      /-\     +-
  \---/   \----/   \---/  
)") + "\033[0m";
	//bored
	Look4 = "\033[38;2;174;198;207m" + std::string(R"(
       ,__,.........     
     /''          '\\    
    /                \   
   /     `.     `.   \   
  /    ,' '-b`,-'\_   \  
  |  _/'     '    ',- |  
  /  ' |  ==  ==  |'  \  
 /     '-........-'    \ 
 |       |      |       | 
 |       /      \       | 
-+     /-\      /-\     +-
  \---/   \----/   \---/      
)") + "\033[0m";

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

	if (skinwalkerAtDoor = true) {
		switch (choice) {
		case 1:
			std::cout << "Attack" << std::endl;
			break;
		case 2:
			std::cout << "Reject them" << std::endl;
			break;
		case 3:
			std::cout << "Let them in" << std::endl;
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

	if (encounteredskinwalker = true) {
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

	if (survivorsAtDoor = true) {
		switch (choice) {
		case 1:
			std::cout << "Attack" << std::endl;
			break;
		case 2:
			std::cout << "Reject them" << std::endl;
			break;
		case 3:
			std::cout << "Let them in" << std::endl;
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
//	if (encounteredsurvivors = true) {
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


