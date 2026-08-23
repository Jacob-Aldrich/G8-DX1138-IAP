#include "Object.h"

Object::Object(char sym, int x, int y, std::string objName)
{
    symbol = sym;
    xPosition = x;
    yPosition = y;
    name = objName;
}

int Object::GetX()
{
    return xPosition;
}

int Object::GetY()
{
    return yPosition;
}

void Object::SetX(int x)
{
    xPosition = x;
}

void Object::SetY(int y)
{
    yPosition = y;
}

char Object::GetSymbol()
{
    return symbol;
}

std::string Object::GetName()
{
    return name;
}

void Object::Interacted()
{
    std::cout << "OBJECT INTERACTED\n";
}

Object::~Object()
{
    
}