#pragma once
#include <iostream>

class World;

class Object
{
protected:
	char symbol;
    int xPosition;
    int yPosition;
    std::string name;
public:
    Object(char sym, int x, int y, std::string name);

    int GetX();
    int GetY();

    void SetX(int x);
    void SetY(int y);

    char GetSymbol();
    std::string GetName();
    virtual bool Interacted();

    virtual ~Object();
};
