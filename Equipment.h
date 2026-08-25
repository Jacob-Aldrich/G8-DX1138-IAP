#pragma once

#include "Object.h"

enum class ItemType
{
	SWORD,
	GUN
};

enum class EquipmentSlot
{
	HAND
};

class Equipment : public Object
{
private:
	ItemType Type;
	EquipmentSlot Slot;

	int AttackValue;

	bool SetsAttackExactly;
	bool InstantDefeat;

	int UsesRemaining;
	int MaximumUses;

public:
	Equipment(
		ItemType type,
		EquipmentSlot slot,
		const std::string& name,
		char symbol,
		int xPosition,
		int yPosition,
		int attackValue,
		bool setsAttackExactly,
		bool instantDefeat,
		int maximumUses
	);

	ItemType GetType();
	EquipmentSlot GetSlot();

	int GetAttackValue();

	bool DoesSetAttackExactly();
	bool IsInstantDefeatGear();

	int GetUsesRemaining();
	int GetMaximumUses();

	bool HasUsesRemaining();
	bool UseOnce();

	void PrintDetails();

	bool Interacted() override;
};