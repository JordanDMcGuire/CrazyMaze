#ifndef H_items
#define H_items

#include <iostream>

using namespace std;

class items 
{
public:
	items(int, int, string, string, int, char);
	string getItemName();
	string getItemType();
	int getItemValue();
	void setItemName(string);
	void setItemType(string);
	void setItemValue(int);
	char getSymbol();
	void setSymbol(char sy);
	int getXPosition();
	int getYPosition();
	void setXPosition(int x);
	void setYPosition(int y);
private:
	string itemName;
	string itemType;
	int itemValue;
	char symbol;
	int yPosition;
	int xPosition;
};
#endif
