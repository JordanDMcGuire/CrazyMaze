#ifndef H_mapObject
#define H_mapObject

#include <iostream>
#include "items.h"

using namespace std;

class mapObject
{
public:
	mapObject();
	int getXPosition();
	int getYPosition();
	int getStrength();
	int getHealth();
	string getName();
	char getSymbol();
	void setXPosition(int x);
	void setYPosition(int y);
	void setStrength(int s);
	void setHealth(int h);
	void setName(string n);
	void setSymbol(char sy);	
	void recieveItem(mapObject&, items&);
	void recieveCurse(mapObject&, items&);
private:
	int yPosition;
	int xPosition;
	int strength;
	int health;
	string name;
	char symbol;
};

#endif
