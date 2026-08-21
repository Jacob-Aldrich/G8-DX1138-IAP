#pragma once

#include "Object.h"

class Material : public Object
{
private:

    int quantity;
    int maximumQuantity;

public:

    Material(int startingQuantity, int startingMaximumQuantity);
	Material(char symbol, int xPosition, int yPosition,
		const std::string& materialName, int startingQuantity,
		int startingMaximumQuantity);

    int GetQuantity();
    int GetMaximumQuantity();

    bool IsEmpty();

    void AddQuantity(int quantityToAdd);

    bool UseQuantity(int quantityToUse);
	void PrintDetails();
};
