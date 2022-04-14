#include "player.h"

// A blank player is a dead player
player::player()
{
    setName("Dead Player");
    setXPosition(0);
    setYPosition(0);
    setHealth(0);
    setStrength(0);
    setSymbol('|');
}

// Player with all values
player::player(int x, int y, int h, int s, string name, char sy)
{
    setName(name);
    setXPosition(x);
    setYPosition(y);
    setHealth(h);
    setStrength(s);
    setSymbol(sy);
}

