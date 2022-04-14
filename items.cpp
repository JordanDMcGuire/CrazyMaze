#include "items.h"

// items are defined like this
items::items(int x, int y, string n, string t, int v, char s)
{
    setXPosition(0);
    setYPosition(0);
    setItemName(n);
    setItemType(t);
    setItemValue(v);
    setSymbol(s);
}

// Accessors and Mutators for Items
string items::getItemName() {
    return this->itemName;
}

string items::getItemType() {
    return this->itemType;
}

int items::getItemValue() {
    return this->itemValue;
}

void items::setItemName(string iN) {
    this->itemName = iN;
}

void items::setItemType(string iT) {
    this->itemType = iT;
}

void items::setItemValue(int iV) {
    this->itemValue = iV;
}

char items::getSymbol()
{
    return this->symbol;
}
void items::setSymbol(char sy)
{
    this->symbol = sy;
}

int items::getXPosition()
{
    return this->xPosition;
}

int items::getYPosition()
{
    return this->yPosition;
}
void items::setXPosition(int x)
{
    this->xPosition = x;
}

void items::setYPosition(int y)
{
    this->yPosition = y;
}
