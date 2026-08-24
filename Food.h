#pragma once
#include "Material.h"
class Food : public Material
{
    Material* foodSupply;
public:
    Food(int startingQuantity, int startingMaximumQuantity, Material* foodSupply);

    bool Interacted() override;
};

