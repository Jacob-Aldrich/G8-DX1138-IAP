#include "Material.h"

#include <iostream>

// initialization
Material::Material(int startingQuantity, int startingMaximumQuantity)
	: Object('?', -1, -1, "Stored Material")
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

Material::Material(char symbol, int xPosition, int yPosition,
	const std::string& materialName, int startingQuantity,
	int startingMaximumQuantity)
	: Object(symbol, xPosition, yPosition, materialName)
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

// returns the quantity
int Material::GetQuantity()
{
    return quantity;
}

// returns the max quantity
int Material::GetMaximumQuantity()
{
    return maximumQuantity;
}

// checks if its empty
bool Material::IsEmpty()
{
    return quantity == 0;
}

// adds the quantity
void Material::AddQuantity(int quantityToAdd)
{
	if (quantityToAdd <= 0)
	{
		return;
	}

    quantity = quantity + quantityToAdd;

    // checks for the max quantity, if its max then cnanot add more
    if (quantity > maximumQuantity)
    {
        quantity = maximumQuantity;
    }
}

// if quan is > 0 and quan is <= than quan then return true
bool Material::UseQuantity(int quantityToUse)
{
    if (quantityToUse > 0 && quantityToUse <= quantity)
    {
        quantity = quantity - quantityToUse;
        return true;
    }

    return false;
}

void Material::PrintDetails()
{
	std::cout << GetObjectName() << " [Material] "
		<< quantity << "/" << maximumQuantity;
}
