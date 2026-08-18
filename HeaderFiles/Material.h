#pragma once

#include "Object.h"

class Material : public Object
{
private:

    int quantity;
    int maximumQuantity;
public:

    Material(int startingQuantity, int startingMaximumQuantity, char startingSymbol, std::string startingName);

    int GetQuantity();
    int GetMaximumQuantity();

    bool IsEmpty();

    void AddQuantity(int quantityToAdd);
    bool UseQuantity(int quantityToUse);
};
