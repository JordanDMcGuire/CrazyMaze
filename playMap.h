#ifndef H_playMap
#define H_playMap

#include "mapObject.h"
#include <iostream>
#include <fstream>
#include "nonPlayer.h"
#include "items.h"

using namespace std;

class playMap {
public:
	playMap();
	int yRows;
	int xColumns;
	string player1TileMover;
	string enemy1TileMover;
	string enemy2TileMover;
	string enemy3TileMover;
	string NPC1TileMover;
	string** mapID;
	string** specialLocations;
	string mapString;
	ifstream playMapTxt;
	void buildMap(string, mapObject&, mapObject&, mapObject&, mapObject&, nonPlayer&, nonPlayer&, nonPlayer&,
		items&, items&, items&);
	void mapPositions(int, mapObject&, mapObject&, mapObject&, mapObject&, nonPlayer&, nonPlayer&, nonPlayer&,
		items&, items&, items&);
	string printMap(mapObject&);
};

#endif