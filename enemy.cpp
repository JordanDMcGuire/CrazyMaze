#include "enemy.h"

// A blank enemy is a dead enemy
enemy::enemy()
{
    setName("Dead Player");
    setXPosition(0);
    setYPosition(0);
    setHealth(0);
    setStrength(0);
    setSymbol('|');
}

// Enemy with all values
enemy::enemy(int x, int y, int h, int s, string name, char sy)
{
    setName(name);
    setXPosition(x);
    setYPosition(y);
    setHealth(h);
    setStrength(s);
    setSymbol(sy);
}