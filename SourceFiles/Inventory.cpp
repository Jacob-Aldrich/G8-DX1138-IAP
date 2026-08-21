#include "Inventory.h"
#include "World.h"

#include <iostream>

Inventory::Inventory()
{
	ItemCount = 0;
	EquippedGear = nullptr;

	for (int i = 0; i < MaximumItems; i++)
	{
		Items[i] = nullptr;
	}
}

Inventory::~Inventory()
{
	for (int i = 0; i < ItemCount; i++)
	{
		delete Items[i];
		Items[i] = nullptr;
	}

	EquippedGear = nullptr;
}

bool Inventory::AddItem(Equipment* equipment)
{
	if (equipment == nullptr || ItemCount >= MaximumItems)
	{
		return false;
	}

	equipment->SetX(-1);
	equipment->SetY(-1);
	Items[ItemCount] = equipment;
	ItemCount++;
	return true;
}

bool Inventory::EquipItem(int inventoryIndex)
{
	Equipment* equipment = GetItem(inventoryIndex);

	if (equipment == nullptr || equipment->GetSlot() != EquipmentSlot::Gear)
	{
		return false;
	}

	EquippedGear = equipment;
	std::cout << "Equipped " << equipment->GetObjectName()
		<< " as your gear.\n";
	return true;
}

void Inventory::ShowInventory(int baseAttack)
{
	std::cout << "\n===== GEAR INVENTORY =====\n";

	if (ItemCount == 0)
	{
		std::cout << "You have not collected any gear.\n";
	}
	else
	{
		for (int i = 0; i < ItemCount; i++)
		{
			std::cout << "[" << i + 1 << "] ";
			Items[i]->PrintDetails();

			if (Items[i] == EquippedGear)
			{
				std::cout << "  (Equipped)";
			}

			std::cout << "\n";
		}
	}

	std::cout << "Gear: ";
	if (EquippedGear != nullptr)
	{
		std::cout << EquippedGear->GetObjectName();
	}
	else
	{
		std::cout << "None";
	}

	std::cout << "\nTotal Attack: " << GetAttackWithGear(baseAttack)
		<< "\n";
}

void Inventory::InventoryMenu(int baseAttack)
{
	ShowInventory(baseAttack);

	if (ItemCount == 0)
	{
		return;
	}

	int choice;
	std::cout << "Choose an item number to equip, or 0 to return.\n> ";
	std::cin >> choice;

	if (choice == 0)
	{
		return;
	}

	if (!EquipItem(choice - 1))
	{
		std::cout << "That gear choice is not available.\n";
	}
}

int Inventory::GetItemCount()
{
	return ItemCount;
}

Equipment* Inventory::GetItem(int inventoryIndex)
{
	if (inventoryIndex < 0 || inventoryIndex >= ItemCount)
	{
		return nullptr;
	}

	return Items[inventoryIndex];
}

Equipment* Inventory::GetEquippedGear()
{
	return EquippedGear;
}

int Inventory::GetAttackWithGear(int baseAttack)
{
	if (EquippedGear == nullptr)
	{
		return baseAttack;
	}

	if (EquippedGear->DoesSetAttackExactly())
	{
		return EquippedGear->GetAttackValue();
	}

	// A loaded Gun uses its instant-defeat effect instead of an Attack bonus.
	if (EquippedGear->IsInstantDefeatGear())
	{
		return baseAttack;
	}

	return baseAttack + EquippedGear->GetAttackValue();
}
