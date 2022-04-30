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
    case 1: // level one

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
        NPC1.setSymbol('!'); //"The Boots of Familiarity", "health", 10
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

    case 2: // level two
        // Level 2 map size
        yRows = 10;
        xColumns = 32;

        // Map array for what the user will see in level 2
        mapID = new string * [yRows];
        for (int i = 0; i < yRows; i++)
            mapID[i] = new string[xColumns];

        // Map array for locations that the user interacts with (ladders, items, nonplayers) in level 2
        specialLocations = new string * [yRows];
        for (int i = 0; i < yRows; i++)
            specialLocations[i] = new string[xColumns];

        // All positions for mapObjects, ladders, items, and nonPlayers
        player.setXPosition(1);
        player.setYPosition(9);
        player.setSymbol('O');
        player.setHealth(85);
        player.setStrength(17);

        enemy1.setXPosition(7);
        enemy1.setYPosition(6);
        enemy1.setSymbol('X');
        enemy1.setHealth(30);
        enemy1.setStrength(7);

        enemy2.setXPosition(10);
        enemy2.setYPosition(3);
        enemy2.setSymbol('X');
        enemy2.setHealth(40);
        enemy2.setStrength(11);

        enemy3.setXPosition(7);
        enemy3.setYPosition(0);
        enemy3.setSymbol('X');
        enemy3.setHealth(50);
        enemy3.setStrength(14);

        NPC1.setXPosition(10);
        NPC1.setYPosition(7);
        NPC1.setSymbol('!'); //"The Chestplate of Minor Swagger", "health", 15
        NPC1.setNPCType("friend");
        NPC1.setItemName("The Chestplate of Minor Swagger");
        NPC1.setItemType("health");
        NPC1.setItemValue(15);

        NPC2.setXPosition(22);
        NPC2.setYPosition(2);
        NPC2.setSymbol('!'); //"Curse of Weak Social Skills", "strength", 5
        NPC2.setNPCType("foe");
        NPC2.setItemName("Curse of Weak Social Skills");
        NPC2.setItemType("strength");
        NPC2.setItemValue(5);

        NPC3.setXPosition(6);
        NPC3.setYPosition(1);
        NPC3.setSymbol('!'); //"Sword of Technical Advantage", "strength", 10
        NPC3.setNPCType("friend");
        NPC3.setItemName("The Sword of Technical Advantage");
        NPC3.setItemType("strength");
        NPC3.setItemValue(10);

        item1.setXPosition(20);
        item1.setYPosition(8);
        item1.setSymbol('='); //"The Ring of Punching", "strength", 3      
        item1.setItemName("The Ring of Punching");
        item1.setItemType("strength");
        item1.setItemValue(3);

        item2.setXPosition(19);
        item2.setYPosition(5);
        item2.setSymbol('='); //"The Flaming Pants of Lies", "health", 10      
        item2.setItemName("The Flaming Pants of Lies");
        item2.setItemType("health");
        item2.setItemValue(10);

        // Ladders
        specialLocations[9][12] = "L1-168";
        specialLocations[8][16] = "L1-129";
        specialLocations[8][25] = "L2-256";
        specialLocations[6][25] = "L2-258";
        specialLocations[6][20] = "L3-167";
        specialLocations[7][16] = "L3-206";
        specialLocations[7][5] = "L4-056";
        specialLocations[6][5] = "L4-057"; 
        specialLocations[6][10] = "L5-145";
        specialLocations[5][14] = "L5-106"; 
        specialLocations[5][24] = "L6-242";
        specialLocations[2][24] = "L6-245"; 
        specialLocations[2][20] = "L7-163";
        specialLocations[3][16] = "L7-202"; 
        specialLocations[3][4] = "L8-041";
        specialLocations[1][4] = "L8-043";
        specialLocations[1][9] = "L9-090";
        specialLocations[0][9] = "L9-091";

        // NPC Interactions
        specialLocations[7][11] = "!0-001";
        specialLocations[2][23] = "!0-002";
        specialLocations[1][5] = "!0-003";

        // Enemy Interactions
        specialLocations[6][6] = "X0-001";
        specialLocations[3][11] = "X0-002";
        specialLocations[0][8] = "X0-003";

        // Items
        specialLocations[8][19] = "=0-001";
        specialLocations[5][18] = "=0-002";
        
        break;

    case 3: // level three
        // Level 3 map size
        yRows = 10;
        xColumns = 32;

        // Map array for what the user will see in level 3
        mapID = new string * [yRows];
        for (int i = 0; i < yRows; i++)
            mapID[i] = new string[xColumns];

        // Map array for locations that the user interacts with (ladders, items, nonplayers) in level 3
        specialLocations = new string * [yRows];
        for (int i = 0; i < yRows; i++)
            specialLocations[i] = new string[xColumns];

        // All positions for mapObjects, ladders, items, and nonPlayers
        player.setXPosition(30);
        player.setYPosition(7);
        player.setSymbol('O');
        player.setHealth(95);
        player.setStrength(15);

        enemy1.setXPosition(7);
        enemy1.setYPosition(8);
        enemy1.setSymbol('X');
        enemy1.setHealth(30);
        enemy1.setStrength(7);

        enemy2.setXPosition(23);
        enemy2.setYPosition(4);
        enemy2.setSymbol('X');
        enemy2.setHealth(40);
        enemy2.setStrength(11);

        enemy3.setXPosition(7);
        enemy3.setYPosition(0);
        enemy3.setSymbol('X');
        enemy3.setHealth(60);
        enemy3.setStrength(14);

        NPC1.setXPosition(15);
        NPC1.setYPosition(9);
        NPC1.setSymbol('!'); //"The Gloves of Friendly Waving", "health", 10
        NPC1.setNPCType("friend");
        NPC1.setItemName("The Gloves of Friendly Waving");
        NPC1.setItemType("health");
        NPC1.setItemValue(10);

        NPC2.setXPosition(7);
        NPC2.setYPosition(4);
        NPC2.setSymbol('!'); //"Curse of Noodle Arms", "strength", 5
        NPC2.setNPCType("foe");
        NPC2.setItemName("Curse of Noodle Arms");
        NPC2.setItemType("strength");
        NPC2.setItemValue(5);

        NPC3.setXPosition(15);
        NPC3.setYPosition(1);
        NPC3.setSymbol('!'); //"Axe of Diminishing Returns", "strength", 3
        NPC3.setNPCType("friend");
        NPC3.setItemName("Axe of Diminishing Returns");
        NPC3.setItemType("strength");
        NPC3.setItemValue(3);

        item1.setXPosition(23);
        item1.setYPosition(8);
        item1.setSymbol('='); //"Necklace of Undeniable Fashion Sense", "health", 12      
        item1.setItemName("Necklace of Undeniable Fashion Sense");
        item1.setItemType("health");
        item1.setItemValue(12);

        item2.setXPosition(15);
        item2.setYPosition(6);
        item2.setSymbol('='); //"A Pretty Decent Looking Sandwich", "health", 10      
        item2.setItemName("A Pretty Decent Looking Sandwich");
        item2.setItemType("health");
        item2.setItemValue(10);

        item3.setXPosition(23);
        item3.setYPosition(2);
        item3.setSymbol('='); //"The Helmet of Headbutting", "strength", 10      
        item3.setItemName("The Helmet of Headbutting");
        item3.setItemType("strength");
        item3.setItemValue(10);

        // Ladders
        specialLocations[7][29] = "L1-258";
        specialLocations[8][25] = "L1-297";
        specialLocations[8][21] = "L2-179";
        specialLocations[9][17] = "L2-218";
        specialLocations[9][13] = "L3-098";
        specialLocations[8][9] = "L3-139";
        specialLocations[8][5] = "L4-054";
        specialLocations[4][5] = "L4-058";
        specialLocations[4][9] = "L5-136";
        specialLocations[6][13] = "L5-094";
        specialLocations[6][17] = "L6-214";
        specialLocations[4][21] = "L6-176";
        specialLocations[4][25] = "L7-252";
        specialLocations[2][25] = "L7-254";
        specialLocations[2][21] = "L8-171";
        specialLocations[1][17] = "L8-212";
        specialLocations[1][13] = "L9-090";
        specialLocations[0][9] = "L9-131";

        // NPC Interactions
        specialLocations[9][16] = "!0-001";
        specialLocations[4][6] = "!0-002";
        specialLocations[1][16] = "!0-003";

        // Enemy Interactions
        specialLocations[8][8] = "X0-001";
        specialLocations[4][22] = "X0-002";
        specialLocations[0][8] = "X0-003";

        // Items
        specialLocations[8][24] = "=0-001";
        specialLocations[6][14] = "=0-002";
        specialLocations[2][24] = "=0-003";

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
