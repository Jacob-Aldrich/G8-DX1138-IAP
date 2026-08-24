#include "Player.h"
//#include "skinwalker.h"
#include <iostream>
#include <string>

Player::Player() : Entity(100, 20), // Initialize base class with health and attack points
	hunger(100),
	thirst(100),
	skinwalkerEncounter(false),
	survivorsEncounter(false),
	breadCount(0),
	waterCount(0),
	medicalKitCount(0)
{
	// Default look for the player
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
	Look1 = "\033[38;2;150;170;255m" + std::string(R"(
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
	//bored
	Look2 = "\033[38;2;174;198;207m" + std::string(R"(
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
	//dead
	Look4 = "\033[38;2;170;0;0m" + std::string(R"(
       ,__,.........      
     /''          '\\     
    /                \    
   /     `.     `.   \    
  /    ,' '-b`,-'\_   \   
  |  _/'  \/ '\/  ',- |   
  /  ' |  /\  /\- |'  \   
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

	if (skinwalkerAtDoor) {
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

//bool Player::EncounterSkinwalker() {
//	bool EncounteredSkinwalker = false;
//	return EncounteredSkinwalker;
//}


void Player::SurvivorsAtDoor(int choice)
{

	bool survivorsAtDoor = false;

	if (survivorsAtDoor) {
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

char Player::GetGridSymbol() {
	if (skinwalkerEncounter || survivorsEncounter) {
		//switch to ASCII art
		std::cout << (skinwalkerEncounter ? GetLook1() : GetLook3()) << std::endl;
		return 'X';
	}
		return 'P';
}

void Player::DisplayStatus() {
	std::cout << "Player [HP: " << GetHealthPoints()
		<< ", ATK: " << GetBaseAttackPoints()
		<< ", Hunger: " << hunger
		<< ", Thirst: " << thirst
		<< "]" << std::endl;
}

// Item pickup
void Player::PickUpBread() {
	if (breadCount < 10) {
		breadCount++;
		std::cout << "Picked up bread! You now have " << breadCount << " bread(s)." << std::endl;
	}
	else {
		std::cout << "Bag full of bread (10 max)." << std::endl;
	}
}

void Player::PickUpWater() {
	if (waterCount < 10) {
		waterCount++;
		std::cout << "Picked up bottle! You now have " << waterCount << " bottle(s)" << std::endl;
	}
	else {
		std::cout << "Bag full of bottle (10 max)" << std::endl;
	}
}

void Player::PickUpKnife() {
	// Assuming knife increases attack points
	int newAttackPoints = GetBaseAttackPoints() + 10; // Increase attack by 10
	std::cout << "Picked up a knife! Attack increased to " << newAttackPoints << std::endl;
	// Note: You might want to implement a method to set the new attack points in Entity class
}

void Player::PickUpMedicalKit() {
	if (medicalKitCount < 10) {
		medicalKitCount++;
		std::cout << "Picked up a medical kit! You now have " << medicalKitCount << " medical kit(s)." << std::endl;
	}
	else {
		std::cout << "Bag full of medical kits (10 max)." << std::endl;
	}
}

//bag actions
void Player::ShowBag() {
	std::cout << "Bag contains: "
		<< breadCount << " bread, "
		<< waterCount << " water, "
		<< medicalKitCount << " medical kits. "
		<< std::endl;
}

void Player::ConsumeBread() {
	if (breadCount > 0) {
		if (hunger == 100) {
			std::cout << "Energy Bar is full!"
				<< " Loaf of bread not consumed. Loaf of bread left: "
				<< breadCount << std::endl;
			return;
		}

		breadCount--;
		hunger += 20; // Increase hunger by 20
		if (hunger > 100) hunger = 100; // Cap hunger at 100
		std::cout << "Consumed a loaf of bread. Energy Bar increased to " << hunger 
			<< ". Loaf of bread left: " << breadCount << std::endl;
	}
	else {
		std::cout << "No loaf of bread to consume." << std::endl;
	}
}

void Player::ConsumeWater() {
	if (waterCount > 0) {
		if (thirst == 100) {
			std::cout << "Hydration Bar is full!"
				<< " Bottle of water not consumed. Bottle left: "
				<< waterCount << std::endl;
			return;
		}

		waterCount--;
		thirst += 20; // Increase thirst by 20
		if (thirst > 100) thirst = 100; // Cap thirst at 100
		std::cout << "Consumed water. Hydration Bar increased to " << thirst 
			<< ". Bottle left: " << waterCount << std::endl;
	}
	else {
		std::cout << "No bottle of water to consume." << std::endl;
	}
}

void Player::ConsumeMedicalKit() {
	if (medicalKitCount > 0) {
		if(GetHealthPoints() == 100) {
			//hp full does not consume medical kit
			std::cout << "Health Bar is full!" 
				<< " Medical kits left: "
				<< medicalKitCount << std::endl;
			return;
		}

		medicalKitCount--;
		int healAmount = 30; // Amount of HP to restore
		int newHP = GetHealthPoints() + healAmount;
		if (newHP > 100) newHP = 100; // Cap HP at 100

		//apply healing(requires setter or negative damage)
		TakeDamage(-(newHP - GetHealthPoints())); // Negative damage to heal

		std::cout << "Used medical kit. HP increased to " << newHP /*GetHealthPoints()*/ 
			<< ". Medical kits left: " 
			<< medicalKitCount << std::endl;
		// Note: You might want to implement a method to set the new health points in Entity class
	}
	else {
		std::cout << "No medical kits to use." << std::endl;
	}
}

void Player::DropBread() {
	if (breadCount > 0) {
		breadCount--;
		std::cout << "Dropped a loaf of bread. Loaf of bread left: " << breadCount << std::endl;
	}
	else {
		std::cout << "No loaf of bread to drop." << std::endl;
	}
}

void Player::DropWater() {
	if (waterCount > 0) {
		waterCount--;
		std::cout << "Dropped a bottle of water. Bottle left: " << waterCount << std::endl;
	}
	else {
		std::cout << "No bottle of water to drop." << std::endl;
	}
}

void Player::DropMedicalKit() {
	if (medicalKitCount > 0) {
		medicalKitCount--;
		std::cout << "Dropped a medical kit. Medical kits left: " << medicalKitCount << std::endl;
	}
	else {
		std::cout << "No medical kits to drop." << std::endl;
	}
}

//Encounters
void Player::EncounterSkinwalker() {
	skinwalkerEncounter = true;
	std::cout << "A mysterious figure has appeared!" << std::endl;
	BattleSkinwalker();
}

void Player::EncounterSurvivors() {
	survivorsEncounter = true;
	std::cout << "A mysterious figure has appeared!" << std::endl;
}

//Battle logic can bring to the battle system, for now just a placeholder
// Battle logic
void Player::BattleSkinwalker() {
	std::cout << "Battle begins with the Skinwalker!" << std::endl;

	int skinwalkerHP = 50;
	int skinwalkerATK = 15;

	while (IsAlive() && skinwalkerHP > 0) {
		// Player attacks
		skinwalkerHP -= Attack();
		std::cout << "You strike the Skinwalker! HP left: " << skinwalkerHP << std::endl;

		if (skinwalkerHP <= 0) {
			std::cout << "You defeated the Skinwalker!" << std::endl;
			skinwalkerEncounter = false;
			return;
		}

		// Skinwalker attacks
		TakeDamage(skinwalkerATK);
		std::cout << "The Skinwalker hits you! Your HP: " << GetHealthPoints() << std::endl;

		if (!IsAlive()) {
			std::cout << "You were defeated by the Skinwalker..." << std::endl;
			return;
		}
	}
}

/*-----------stays here-----------*/
void Player::SetHunger(int value) {
	hunger = (value > 100 ? 100 : (value < 0 ? 0 : value));
}
void Player::SetThirst(int value) {
	thirst = (value > 100 ? 100 : (value < 0 ? 0 : value));
}

int Player::GetHunger() const {
	return hunger;
}

int Player::GetThirst() const {
	return thirst;
}

void Player::UpdateOverTime() {
	if (hunger > 0) hunger -= 1;
	if (thirst > 0) thirst -= 1;
	//warning if 20%>
	if (hunger <= 20 && hunger > 0) {
		std::cout << "WARNING: Engery Bar is critically low (" << hunger << "%)!" << std::endl;
	}
	if (thirst <= 20 && thirst > 0) {
		std::cout << "WARNING: Hydration Bar is critically low (" << thirst << "%)!" << std::endl;
	}
	//if 0% health bar decrease
	if (hunger == 0 || thirst == 0) {
		int newHP = GetHealthPoints() - 1;
		if (newHP < 0)newHP = 0;
		TakeDamage(1); //decrease HP by 1
		
		if (GetHealthPoints() <= 20 && GetHealthPoints() > 0) {
			std::cout << "WARNING: Health Bar is critically low (" << GetHealthPoints() << "%)!" << std::endl;
		}
		if (GetHealthPoints() == 0) {
			std::cout << "You have died due to Starvation/Dehydration..." << std::endl;
		}
	}
}

/*can put in endings*/
bool Player::IsDead() {
	return GetHealthPoints() <= 0;
}
