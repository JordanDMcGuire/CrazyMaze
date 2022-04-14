#ifndef H_enemy
#define H_enemy

#include <iostream>
#include "mapObject.h"

using namespace std;

class enemy : public mapObject
{
public:
	enemy();
	enemy(int, int, int, int, string, char);
};
#endif
