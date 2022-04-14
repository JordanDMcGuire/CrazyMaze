#ifndef H_player
#define H_player

#include <iostream>
#include "mapObject.h"

using namespace std;

class player : public mapObject
{
public:
	player();
	player(int, int, int, int, string, char);
};
#endif