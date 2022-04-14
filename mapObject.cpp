#include "mapObject.h"
#include <iostream>

using namespace std;

mapObject::mapObject()
{

}

int mapObject::getXPosition()
{
	return this -> xPosition;
}

int mapObject::getYPosition()
{
	return this -> yPosition;
}

int mapObject::getStrength()
{
	return this -> strength;
}

int mapObject::getHealth()
{
	return this -> health;
}

string mapObject::getName()
{
	return this -> name;
}

char mapObject::getSymbol()
{
	return this -> symbol;
}

void mapObject::setXPosition(int x)
{
	this -> xPosition = x;
}

void mapObject::setYPosition(int y)
{
	this -> yPosition = y;
}

void mapObject::setStrength(int s)
{
	this -> strength = s;
}

void mapObject::setHealth(int h)
{
	this -> health = h;
}

void mapObject::setName(string n)
{
	this -> name = n;
}

void mapObject::setSymbol(char sy)
{
	this -> symbol = sy;
}

void mapObject::recieveItem(mapObject& player, items& item)
{
	if (item.getItemType() == "health") {
		player.setHealth(player.getHealth() + item.getItemValue());
	}
	else if (item.getItemType() == "strength") {
		player.setStrength(player.getStrength() + item.getItemValue());
	}
	cout << "You recieved " << item.getItemName() << "!" << endl;
	cout << "Your " << item.getItemType() << " increased by " << item.getItemValue() << "!" << endl;
}

void mapObject::recieveCurse(mapObject& player, items& item)
{
	if (item.getItemType() == "health") {
		player.setHealth(player.getHealth() - item.getItemValue());
	}
	else if (item.getItemType() == "strength") {
		player.setStrength(player.getStrength() - item.getItemValue());
	}
	cout << "You were hit with the " << item.getItemName() << "!" << endl;
	cout << "Your " << item.getItemType() << " decreased by " << item.getItemValue() << "!" << endl;
}


