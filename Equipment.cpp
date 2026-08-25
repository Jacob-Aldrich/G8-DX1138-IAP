#include "Equipment.h"
#include "World.h"

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
	return true;
}

void Equipment::PrintDetails()
{
	std::cout << GetName() << " [Gear]";

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

bool Equipment::Interacted()
{
	std::cout << "You found " << GetName() << ".\n";
	return true;
}