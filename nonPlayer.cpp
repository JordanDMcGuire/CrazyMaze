#include "nonPlayer.h"

// A blank nonPlayer is a dead nonPlayer
nonPlayer::nonPlayer()
{
    setName("Dead Non-Player");
    setXPosition(0);
    setYPosition(0);
    setHealth(0);
    setStrength(0);
    setSymbol('|');
}

// Non-Player with all values
nonPlayer::nonPlayer(int x, int y, int h, int s, string name, char sy, string nType, string iN, string iT, int iV)
{
    setName(name);
    setXPosition(x);
    setYPosition(y);
    setHealth(h);
    setStrength(s);
    setSymbol(sy);
    setNPCType(nType);
    setItemName(iN);
    setItemType(iT);
    setItemValue(iV);
}

// The nonPlayer gives the player an item for free
void nonPlayer::kind(mapObject& player) {
    cout << "You seem lost! Here, this might help you." << endl;
    cout << "The kind stranger gives you an item!" << endl;
    items freeItem(0, 0, itemName, itemType, itemValue, '*');
    recieveItem(player, freeItem);
}

// The nonPlayer curses the player
void nonPlayer::curse(mapObject& player) {
    cout << "Be gone, outsider!" << endl;
    cout << "The evil stranger curses you!" << endl;
    items freeItem(0, 0, itemName, itemType, itemValue, '*');
    recieveCurse(player, freeItem);
}

// Accessors and Mutators for Items
string nonPlayer::getItemName() {
    return this->itemName;
}

string nonPlayer::getItemType() {
    return this->itemType;
}

int nonPlayer::getItemValue() {
    return this->itemValue;
}

void nonPlayer::setItemName(string iN) {
    this->itemName = iN;
}

void nonPlayer::setItemType(string iT) {
    this->itemType = iT;
}

void nonPlayer::setItemValue(int iV) {
    this->itemValue = iV;
}

void nonPlayer::setNPCType(string nType) {
    this->npcType = nType;
}
string nonPlayer::getNPCType() {
    return this->npcType;
}