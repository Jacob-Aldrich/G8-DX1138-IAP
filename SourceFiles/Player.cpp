#include "Player.h"
#include "World.h"

#include <iostream>
#include <string>

Player::Player() : Entity("Player", false, 'P')
{
	// The five looks come from the latest main-branch Player refactor.
	Look0 = R"(
       ,__,.........
     /''          '\\
    /                \
   /     `.     `.    \
  /    ,' '-b`,-'\_    \
  |  _/'  o  ' o  ',-  |
  /  ' |          |'    \
 /     '-........-'      \
 |       |      |         |
 |       /      \         |
-+     /-\      /-\       +-
  \---/   \----/   \---/
)";

	Look1 = R"(
       ,__,.........
     /''          '\\
    /                \
   /     `.     `.    \
  /    ,' '-b`,-'\_    \
  |  _/' ,\  '/,  ',-  |
  /  ' |  '   '   |'    \
 /     '-........-'      \
 |       |      |         |
 |       /      \         |
-+     /-\      /-\       +-
  \---/   \----/   \---/
)";

	Look2 = R"(
       ,__,.........
     /''          '\\
    /                \
   /     `.     `.    \
  /    ,' '-b`,-'\_    \
  |  _/'  __' __  ',-  |
  /  ' |  |    |  |'    \
 /     '-........-'      \
 |       |      |         |
 |       /      \         |
-+     /-\      /-\       +-
  \---/   \----/   \---/
)";

	Look3 = R"(
       ,__,.........
     /''          '\\
    /                \
   /     `.     `.    \
  /    ,' '-b`,-'\_    \
  |  _/' ,_  '_.  ',-  |
  /  ' | ()   ()  |'    \
 /     '-.. O ...-'      \
 |       |      |         |
 |       /      \         |
-+     /-\      /-\       +-
  \---/   \----/   \---/
)";

	Look4 = R"(
       ,__,.........
     /''          '\\
    /                \
   /     `.     `.    \
  /    ,' '-b`,-'\_    \
  |  _/'     '    ',-  |
  /  ' |  ==  ==  |'    \
 /     '-........-'      \
 |       |      |         |
 |       /      \         |
-+     /-\      /-\       +-
  \---/   \----/   \---/
)";

	Dialogue1 = "\"It's been a while\"";
	Dialogue2 = "\"Who are you?\"";
	Dialogue3 = "\"No!\"";
}

Player::~Player()
{
}

bool Player::AddEquipment(Equipment* equipment)
{
	return GearInventory.AddItem(equipment);
}

bool Player::EquipItem(int inventoryIndex)
{
	return GearInventory.EquipItem(inventoryIndex);
}

void Player::ShowEquipment()
{
	GearInventory.ShowInventory(GetBaseAttackPoints());
}

void Player::EquipmentMenu()
{
	GearInventory.InventoryMenu(GetBaseAttackPoints());
}

int Player::GetEquipmentCount()
{
	return GearInventory.GetItemCount();
}

Equipment* Player::GetEquipment(int inventoryIndex)
{
	return GearInventory.GetItem(inventoryIndex);
}

Equipment* Player::GetEquippedGear()
{
	return GearInventory.GetEquippedGear();
}

int Player::GetTotalAttackPoints()
{
	return GearInventory.GetAttackWithGear(GetBaseAttackPoints());
}

void Player::Speak(int choice)
{
	if (choice == 1)
	{
		std::cout << Dialogue1 << std::endl;
	}
	else if (choice == 2)
	{
		std::cout << Dialogue2 << std::endl;
	}
	else if (choice == 3)
	{
		std::cout << Dialogue3 << std::endl;
	}
	else
	{
		std::cout << "..." << std::endl;
	}
}

std::string Player::GetLook0()
{
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
	if (choice == 1)
	{
		std::cout << "Attack" << std::endl;
	}
	else if (choice == 2)
	{
		std::cout << "Reject them" << std::endl;
	}
	else if (choice == 3)
	{
		std::cout << "Let them in" << std::endl;
	}
	else
	{
		std::cout << "..." << std::endl;
	}
}

void Player::EncounterSkinwalker(int choice)
{
	if (choice == 1)
	{
		std::cout << "Battle" << std::endl;
	}
	else
	{
		std::cout << "..." << std::endl;
	}
}

bool Player::SkinwalkerAtDoor()
{
	return false;
}

bool Player::EncounterSkinwalker()
{
	return false;
}

void Player::SurvivorsAtDoor(int choice)
{
	if (choice == 1)
	{
		std::cout << "Attack" << std::endl;
	}
	else if (choice == 2)
	{
		std::cout << "Reject them" << std::endl;
	}
	else if (choice == 3)
	{
		std::cout << "Let them in" << std::endl;
	}
	else
	{
		std::cout << "..." << std::endl;
	}
}

bool Player::SurvivorsAtDoor()
{
	return false;
}
