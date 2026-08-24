#pragma once
#include "Object.h"
class House : public Object
{

public:
	House(char sym, int x, int y, std::string name);
	bool Interacted() override;
};

