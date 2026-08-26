#include "Inventory.h"
#include "Equipment.h"
#include "Material.h"

#include <iostream>

//brandon
Inventory::Inventory()
{
	ItemCount = 0;
	CapacityBonus = 0;
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

	delete EquippedGear;
	EquippedGear = nullptr;
}

bool Inventory::AddItem(Object* object)
{
	if (object == nullptr)
	{
		return false;
	}

	if (ItemCount >= GetMaximumItems())
	{
		return false;
	}

	object->SetX(-1);
	object->SetY(-1);

	Items[ItemCount] = object;
	ItemCount++;

	return true;
}

bool Inventory::RemoveItem(int inventoryIndex)
{
	if (inventoryIndex < 0 || inventoryIndex >= ItemCount)
	{
		return false;
	}

	Items[inventoryIndex] = nullptr;

	for (int i = inventoryIndex; i < ItemCount - 1; i++)
	{
		Items[i] = Items[i + 1];
	}

	Items[ItemCount - 1] = nullptr;
	ItemCount--;

	return true;
}

Object* Inventory::TakeItem(int inventoryIndex)
{
	if (inventoryIndex < 0 || inventoryIndex >= ItemCount)
	{
		return nullptr;
	}

	Object* item = Items[inventoryIndex];
	for (int i = inventoryIndex; i < ItemCount - 1; i++)
	{
		Items[i] = Items[i + 1];
	}
	Items[ItemCount - 1] = nullptr;
	ItemCount--;
	return item;
}

void Inventory::SetCapacityBonus(int bonus)
{
	CapacityBonus = bonus < 0 ? 0 : bonus;
}

bool Inventory::EquipItem(int inventoryIndex)
{
	if (inventoryIndex < 0 || inventoryIndex >= ItemCount)
	{
		return false;
	}

	Equipment* equipment =
		dynamic_cast<Equipment*>(Items[inventoryIndex]);

	if (equipment == nullptr)
	{
		return false;
	}

	if (EquippedGear != nullptr)
	{
		std::cout << "You already have "
			<< EquippedGear->GetName()
			<< " equipped.\n";

		return false;
	}

	EquippedGear = equipment;

	// Remove it from the inventory WITHOUT deleting it.
	for (int i = inventoryIndex; i < ItemCount - 1; i++)
	{
		Items[i] = Items[i + 1];
	}

	Items[ItemCount - 1] = nullptr;
	ItemCount--;

	std::cout << "Equipped "
		<< EquippedGear->GetName()
		<< ".\n";

	return true;
}

bool Inventory::EquipEquipment(Equipment* equipment)
{
	if (equipment == nullptr)
	{
		return false;
	}

	if (EquippedGear != nullptr)
	{
		std::cout << "You already have "
			<< EquippedGear->GetName()
			<< " equipped.\n";

		return false;
	}

	EquippedGear = equipment;

	std::cout << "Equipped "
		<< EquippedGear->GetName()
		<< ".\n";

	return true;
}

bool Inventory::StoreEquippedItem()
{
	if (EquippedGear == nullptr)
	{
		return false;
	}

	if (ItemCount >= GetMaximumItems())
	{
		std::cout << "Your inventory is full.\n";
		return false;
	}

	Items[ItemCount] = EquippedGear;
	ItemCount++;

	std::cout << "Stored "
		<< EquippedGear->GetName()
		<< " in your inventory.\n";

	EquippedGear = nullptr;

	return true;
}

Equipment* Inventory::GetEquippedGear()
{
	return EquippedGear;
}

void Inventory::ShowInventory()
{
	std::cout << "\n";
	std::cout << "INVENTORY MENU\n";
	std::cout << "---------------\n";

	if (ItemCount == 0)
	{
		std::cout << "[EMPTY]\n";
	}
	else
	{
		for (int i = 0; i < ItemCount; i++)
		{
			std::cout << "[" << i + 1 << "] "
				<< Items[i]->GetName();

			Equipment* equipment =
				dynamic_cast<Equipment*>(Items[i]);

			if (equipment != nullptr)
			{
				std::cout << " [Equipment]";
			}

			std::cout << "\n";
		}
	}

	std::cout << "\nInventory Storage "
		<< ItemCount
		<< "/"
		<< MaximumItems
		<< "\n";

	if (EquippedGear != nullptr)
	{
		std::cout << "EQUIPPED ITEM: ["
			<< EquippedGear->GetName()
			<< "]\n";
	}
	else
	{
		std::cout << "EQUIPPED ITEM: [NONE]\n";
	}
}

void Inventory::InventoryMenu()
{
	ShowInventory();
}

void Inventory::HouseInventoryMenu()
{
	std::cout << "\n";
	std::cout << "INVENTORY MENU\n";
	std::cout << "---------------\n";

	std::cout << "Food Supply: Stored separately\n";
	std::cout << "Water Supply: Stored separately\n\n";

	if (ItemCount == 0)
	{
		std::cout << "[EMPTY]\n";
	}
	else
	{
		for (int i = 0; i < ItemCount; i++)
		{
			std::cout << "["
				<< Items[i]->GetName()
				<< "] x1\n";
		}
	}

	std::cout << "\nInventory Storage "
		<< ItemCount
		<< "/"
		<< MaximumItems
		<< "\n";

	if (EquippedGear != nullptr)
	{
		std::cout << "EQUIPPED ITEM: ["
			<< EquippedGear->GetName()
			<< "]\n";
	}
	else
	{
		std::cout << "EQUIPPED ITEM: [NONE]\n";
	}
}

void Inventory::TransferSupplies(
	Material* foodSupply,
	Material* waterSupply
)
{
	for (int i = 0; i < ItemCount;)
	{
		if (Items[i] == nullptr)
		{
			i++;
			continue;
		}

		Material* material =
			dynamic_cast<Material*>(Items[i]);

		if (material != nullptr)
		{
			if (material->GetName() == "Food")
			{
				foodSupply->AddQuantity(
					material->GetQuantity()
				);

				delete Items[i];

				for (int j = i; j < ItemCount - 1; j++)
				{
					Items[j] = Items[j + 1];
				}

				Items[ItemCount - 1] = nullptr;
				ItemCount--;

				continue;
			}

			if (material->GetName() == "Water")
			{
				waterSupply->AddQuantity(
					material->GetQuantity()
				);

				delete Items[i];

				for (int j = i; j < ItemCount - 1; j++)
				{
					Items[j] = Items[j + 1];
				}

				Items[ItemCount - 1] = nullptr;
				ItemCount--;

				continue;
			}
		}

		i++;
	}
}

int Inventory::GetItemCount()
{
	return ItemCount;
}

int Inventory::GetMaximumItems()
{
	return BaseCapacity + CapacityBonus;
}

Object* Inventory::GetItem(int inventoryIndex)
{
	if (inventoryIndex < 0 || inventoryIndex >= ItemCount)
	{
		return nullptr;
	}

	return Items[inventoryIndex];
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

	if (EquippedGear->IsInstantDefeatGear())
	{
		return baseAttack;
	}

	return baseAttack + EquippedGear->GetAttackValue();
}