#pragma once
#include "Material.h"

class Water : public Material
{
public:    
    Water(int startingQuantity, int startingMaximumQuantity);
    void Interacted() override;
};

