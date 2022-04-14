#include <iostream>
#include <fstream>
#include <sstream>
#include "playMap.h"

using namespace std;

// Initialize the variables inside of the map that will keep track of its state.
playMap::playMap()
{

    // Initial values for map arrays
    yRows = 0;
    xColumns = 0;

    // Map array for what the user will see (empty at first)
    mapID = new string * [yRows];
    for (int i = 0; i < yRows; i++)
        mapID[i] = new string[xColumns];

    // Map array for locations that the user interacts with (ladders, items, nonplayers) (empty at first)
    specialLocations = new string * [yRows];
    for (int i = 0; i < yRows; i++)
        specialLocations[i] = new string[xColumns];

    // String that keeps track of the printable state of the map
    mapString = "";
}

// Function that can use mapID and mapString to create/update the map in memory and then store it in a string
void playMap::buildMap(string mapNumber, mapObject& player, mapObject& enemy1, mapObject& enemy2, mapObject& enemy3,
    nonPlayer& NPC1, nonPlayer& NPC2, nonPlayer& NPC3, items& item1, items& item2, items& item3)
{	
    mapString = "";
    string txt = ".txt";

    // Look for txt file containing level data
    try {
        playMapTxt.open("../CrazyMaze/playmap" + mapNumber + txt);
        if (!playMapTxt.is_open()) {    // If the file is not found or not opened succesfully
            throw txt;
        }
    }
    catch (string txt) {
        cout << txt + " file could not be located";    // notify user that file was not found
    }
    
    // Draw the top border of the map
    mapString.append("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    // Read the file containing the level data into the mapID array.
    for (int i = 0; i < yRows; i++) {
        for (int j = 0; j < xColumns; j++) {
            playMapTxt >> mapID[i][j];
        }
    }

    // Store the tile that mapObjects are on so that they can be replaced when the object moves
    player1TileMover = mapID[player.getYPosition()][player.getXPosition()];
    enemy1TileMover = mapID[enemy1.getYPosition()][enemy1.getXPosition()];

    // Update the tile that mapObjects are on with their appropriate symbol
    mapID[player.getYPosition()][player.getXPosition()] = player.getSymbol();
    mapID[enemy1.getYPosition()][enemy1.getXPosition()] = enemy1.getSymbol();
    mapID[enemy2.getYPosition()][enemy2.getXPosition()] = enemy2.getSymbol();
    mapID[enemy3.getYPosition()][enemy3.getXPosition()] = enemy3.getSymbol();
    mapID[NPC1.getYPosition()][NPC1.getXPosition()] = NPC1.getSymbol();
    mapID[NPC2.getYPosition()][NPC2.getXPosition()] = NPC2.getSymbol();
    mapID[NPC3.getYPosition()][NPC3.getXPosition()] = NPC3.getSymbol();
    mapID[item1.getYPosition()][item1.getXPosition()] = item1.getSymbol();
    mapID[item2.getYPosition()][item2.getXPosition()] = item2.getSymbol();
    mapID[item3.getYPosition()][item3.getXPosition()] = item3.getSymbol();

    // Draw the map into mapString
    for (int i = 0; i < yRows; i++) {
        for (int j = 0; j < xColumns; j++) {

            mapString.append(mapID[i][j]);

        }
        mapString.append("\n");

    }
    
    // Draw the bottom border of the map
    mapString.append("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");

}

// Set up all of the relevent map information for each level
void playMap::mapPositions(int mapNumber, mapObject& player, mapObject& enemy1, mapObject& enemy2, mapObject& enemy3,
    nonPlayer& NPC1, nonPlayer& NPC2, nonPlayer& NPC3, items& item1, items& item2, items& item3)
{
    switch (mapNumber) {
    case 1:

        // Level 1 map size
        yRows = 10;
        xColumns = 32;

        // Map array for what the user will see in level 1
        mapID = new string * [yRows];
        for (int i = 0; i < yRows; i++)
            mapID[i] = new string[xColumns];

        // Map array for locations that the user interacts with (ladders, items, nonplayers) in level 1
        specialLocations = new string * [yRows];
        for (int i = 0; i < yRows; i++)
            specialLocations[i] = new string[xColumns];

        // All positions for mapObjects, ladders, items, and nonPlayers
        player.setXPosition(30);
        player.setYPosition(9);
        player.setSymbol('O');
        player.setHealth(85);
        player.setStrength(17);

        enemy1.setXPosition(17);
        enemy1.setYPosition(4);
        enemy1.setSymbol('X');
        enemy1.setHealth(50);
        enemy1.setStrength(11);

        enemy2.setXPosition(7);
        enemy2.setYPosition(0);
        enemy2.setSymbol('X');
        enemy2.setHealth(50);
        enemy2.setStrength(14);

        NPC1.setXPosition(22);
        NPC1.setYPosition(6);
        NPC1.setSymbol('!'); //"The Boots of Familiarity", "health", 15
        NPC1.setNPCType("friend");
        NPC1.setItemName("The Boots of Familiarity");
        NPC1.setItemType("health");
        NPC1.setItemValue(10);

        NPC2.setXPosition(17);
        NPC2.setYPosition(1);
        NPC2.setSymbol('!'); //"Curse of Total Buzzkill", "strength", 5
        NPC2.setNPCType("foe");
        NPC2.setItemName("Curse of Total Buzzkill");
        NPC2.setItemType("strength");
        NPC2.setItemValue(5);

        item1.setXPosition(18);
        item1.setYPosition(8);
        item1.setSymbol('='); //"Dagger of Letter Opening", "strength", 4      
        item1.setItemName("Dagger of Letter Opening");
        item1.setItemType("strength");
        item1.setItemValue(4);

        item2.setXPosition(5);
        item2.setYPosition(7);
        item2.setSymbol('='); //"Pants of Laundry Day", "strength", 2      
        item2.setItemName("Pants of Laundry Day");
        item2.setItemType("strength");
        item2.setItemValue(2);

        item3.setXPosition(10);
        item3.setYPosition(2);
        item3.setSymbol('='); //"Apple of A Few Days Ago", "health", 13      
        item3.setItemName("Apple of A Few Days Ago");
        item3.setItemType("health");
        item3.setItemValue(13);

        // Ladders
        specialLocations[9][25] = "L1-218";
        specialLocations[8][21] = "L1-259";
        specialLocations[8][16] = "L2-166";
        specialLocations[6][16] = "L2-168";
        specialLocations[6][27] = "L3-274";
        specialLocations[4][27] = "L3-276";
        specialLocations[4][11] = "L4-077";
        specialLocations[7][7] = "L4-114";
        specialLocations[7][4] = "L5-042";
        specialLocations[2][4] = "L5-047";
        specialLocations[2][19] = "L6-191";
        specialLocations[1][19] = "L6-192";
        specialLocations[1][13] = "L7-090";
        specialLocations[0][9] = "L7-131";

        // NPC Interactions
        specialLocations[6][21] = "!0-001";
        specialLocations[1][18] = "!0-002";

        // Enemy Interactions
        specialLocations[4][18] = "X0-001";
        specialLocations[0][8] = "X0-002";
        
        // Items
        specialLocations[8][19] = "=0-001";
        specialLocations[7][6] = "=0-002";
        specialLocations[2][9] = "=0-003";
                
        break;
    case 2: // level two coming soon!
        break;
    case 3: // level three coming soon!
        break;
    }
}

string playMap::printMap(mapObject& player)
{

    string health;
    stringstream printHealth;
    printHealth << player.getHealth();
    health = printHealth.str();

    string strength;
    stringstream printStrength;
    printStrength << player.getStrength();
    strength = printStrength.str();

	mapString = mapString + "\n| O - Player | X - Enemy | ! - Stranger | <-> - Ladder | G = Goal |\n";
    mapString = mapString + "| = - Item | Player Health - ";    
    mapString = mapString + health;

    mapString = mapString + " | Player Strength - ";
    mapString = mapString + strength;
    mapString = mapString + " |\n";

    return mapString;
}
