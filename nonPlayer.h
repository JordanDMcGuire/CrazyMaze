#ifndef H_nonPlayer
#define H_nonPlayer

#include <iostream>
#include "mapObject.h"
#include "items.h"

using namespace std;

class nonPlayer : public mapObject
{
public:
	nonPlayer();
	nonPlayer(int, int, int, int, string, char, string, string, string, int);
	void kind(mapObject&);
	void curse(mapObject&);
	string getItemName();
	string getItemType();
	int getItemValue();
	void setItemName(string);
	void setItemType(string);
	void setItemValue(int);
	void setNPCType(string);
	string getNPCType();
private:
	string itemName;
	string itemType;
	int itemValue;
	string npcType;
};
#endif#pragma once
