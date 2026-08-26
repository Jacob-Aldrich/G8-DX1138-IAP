#pragma once

#include "Material.h"
//junlong

class Food : public Material
{
public:
	Food(
		int startingQuantity,
		int startingMaximumQuantity
	);

	bool Interacted() override;
};