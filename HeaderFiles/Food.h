#pragma once
#include "Material.h"
class Food : public Material
{
public:
    Food(int startingQuantity, int startingMaximumQuantity);

    void Interacted() override;
};

