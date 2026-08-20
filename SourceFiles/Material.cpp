#include "Material.h"
#include "Object.h"

// initialization
Material::Material(int startingQuantity, int startingMaximumQuantity, char startingSymbol, std::string startingName) : Object(startingSymbol, 0, 0, startingName)
{
    maximumQuantity = startingMaximumQuantity;
    quantity = startingQuantity;

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

void Material::Interacted()
{

}
