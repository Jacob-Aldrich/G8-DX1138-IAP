#pragma once
#include "Material.h"

class Water : public Material
{
    Material* waterSupply;
public:    
    Water(int startingQuantity, int startingMaximumQuantity, Material* waterSupply);
    bool Interacted() override;
};

