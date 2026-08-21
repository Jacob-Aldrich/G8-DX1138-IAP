#include "Equipment.h"
#include "World.h"

#include <iostream>

Equipment::Equipment(ItemType type, EquipmentSlot slot,
	const std::string& name, char symbol,
	int xPosition, int yPosition,
	int attackValue, bool setsAttackExactly,
	bool instantDefeat, int maximumUses)
	: Object(symbol, xPosition, yPosition, name)
{
	Type = type;
	Slot = slot;
	AttackValue = attackValue;
	SetsAttackExactly = setsAttackExactly;
	InstantDefeat = instantDefeat;
	MaximumUses = maximumUses;

	if (MaximumUses < 0)
	{
		MaximumUses = 0;
	}

	UsesRemaining = MaximumUses;
}

ItemType Equipment::GetType()
{
	return Type;
}

EquipmentSlot Equipment::GetSlot()
{
	return Slot;
}

int Equipment::GetAttackValue()
{
	return AttackValue;
}

bool Equipment::DoesSetAttackExactly()
{
	// The Real Knife always sets Attack exactly. The Gun only uses its
	// normal Attack value after all six instant-defeat uses are gone.
	return SetsAttackExactly ||
		(InstantDefeat && !HasUsesRemaining());
}

bool Equipment::IsInstantDefeatGear()
{
	return InstantDefeat;
}

int Equipment::GetUsesRemaining()
{
	return UsesRemaining;
}

int Equipment::GetMaximumUses()
{
	return MaximumUses;
}

bool Equipment::HasUsesRemaining()
{
	return UsesRemaining > 0;
}

bool Equipment::UseOnce()
{
	if (!HasUsesRemaining())
	{
		return false;
	}

	UsesRemaining--;

	if (InstantDefeat && UsesRemaining == 0)
	{
		ObjectName = "Empty Gun";
	}

	return true;
}

void Equipment::PrintDetails()
{
	std::cout << GetObjectName() << " [Gear]";

	if (InstantDefeat && HasUsesRemaining())
	{
		std::cout << "  Instantly defeats one enemy"
			<< "  Uses " << UsesRemaining << "/" << MaximumUses;
	}
	else if (DoesSetAttackExactly())
	{
		std::cout << "  Sets Attack to " << AttackValue;
	}
	else if (AttackValue > 0)
	{
		std::cout << "  Attack +" << AttackValue;
	}
}
