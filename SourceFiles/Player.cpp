#include "Player.h"
#include <iostream>
#include <string>

Player::Player() : Entity(100, 20) // Initialize base class with health and attack points
{
	Look = R"(                                                      
              -  *****-                        
            *:           %*                    
         .+                -#                  
        :       .------                        
         =     .:            .-+               
        + -.: =              .- =              
        : -.=-.     :     :: .- +              
        - :+- .=             .-.-              
        +                                      
        +      =:            +                 
        +      %    ++++++++ .-                
        +      -:            #                 
        =                                      
               
)"; // Default look for the player
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

void Player::SetLook(const std::string& look) {
	Look = look;
}

std::string Player::GetLook() {
	return Look;
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
		case 2:
			std::cout << "Run away" << std::endl;
			break;
		case 3:
			std::cout << "Befriend them" << std::endl;
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

