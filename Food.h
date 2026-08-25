#pragma once

#include "Material.h"

class Player;

class Food : public Material
{
public:
	Food(
		int startingQuantity,
		int startingMaximumQuantity
	);

	bool Interacted(Player* player);

	bool Interacted() override;
};