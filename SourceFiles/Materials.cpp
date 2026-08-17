#include "Material.h"

Material::Material(int startingQuantity, int startingMaximumQuantity)
{
    maximumQuantity = startingMaximumQuantity;
    quantity = startingQuantity;

    if (maximumQuantity < 0)
    {
        maximumQuantity = 0;
    }

    if (quantity < 0)
    {
        quantity = 0;
    }
    else if (quantity > maximumQuantity)
    {
        quantity = maximumQuantity;
    }
}

int Material::GetQuantity()
{
    return quantity;
}

int Material::GetMaximumQuantity()
{
    return maximumQuantity;
}

bool Material::IsEmpty()
{
    return quantity == 0;
}

void Material::AddQuantity(int quantityToAdd)
{
    if (quantityToAdd > 0)
    {
        quantity = quantity + quantityToAdd;

        if (quantity > maximumQuantity)
        {
            quantity = maximumQuantity;
        }
    }
}

bool Material::UseQuantity(int quantityToUse)
{
    if (quantityToUse > 0 && quantityToUse <= quantity)
    {
        quantity = quantity - quantityToUse;
        return true;
    }

    return false;
}
