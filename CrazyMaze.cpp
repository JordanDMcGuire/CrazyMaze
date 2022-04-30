// CrazyMaze.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <sstream>
#include <thread>
#include <chrono>
#include "player.h"
#include "enemy.h"
#include "nonPlayer.h"
#include "mapObject.h"
#include "playMap.h"
#include "items.h"

using namespace std;

player player1(0, 0, 15, 100, "Crazy Dave", '|');
items item1(0, 0, "", "", 0, '|');
items item2(0, 0, "", "", 0, '|');
items item3(0, 0, "", "", 0, '|');
enemy enemy1(0, 0, 15, 100, "Crazy Goblin", '|');
enemy enemy2(0, 0, 15, 100, "Crazy Orc", '|');
enemy enemy3(0, 0, 15, 100, "Crazy Dragon", '|');
nonPlayer NPC1(0, 0, 1, 1, "Crazy Carl", '|', "", "", "", 0);
nonPlayer NPC2(0, 0, 1, 1, "Crazy Brandon", '|', "", "", "", 0);
nonPlayer NPC3(0, 0, 1, 1, "Crazy Steve", '|', "", "", "", 0);
playMap map1;
playMap map2;
playMap map3;
string currentMap = "1";
string direction = "";
bool inputRecieved = false;
bool moveFinished = false;
bool playing = true;

// Special behaviors for ladders, nonplayers, items
void special(playMap& map) {

    // Break up location data
    string typeRef = map.specialLocations[player1.getYPosition()][player1.getXPosition()].substr(0, 1);
    string xRef = map.specialLocations[player1.getYPosition()][player1.getXPosition()].substr(3, 2);
    string yRef = map.specialLocations[player1.getYPosition()][player1.getXPosition()].substr(5, 1);

    // Check if xRef is single digit
    if (xRef.substr(0, 1) == "0") {
        xRef = xRef.substr(1, 1);
    }

    // Change type data to char
    stringstream typeVal(typeRef);
    char type = ' ';
    typeVal >> type;

    // Change location data to int
    stringstream xVal(xRef);
    stringstream yVal(yRef);
    int x = 0;
    int y = 0;
    xVal >> x;
    yVal >> y;

    // Perform relevent action
    switch (type) {
    case 'L':   // Ladder next to player
        map.mapID[player1.getYPosition()][player1.getXPosition()] = map.player1TileMover;
        player1.setXPosition(x);
        player1.setYPosition(y);
        // here
        map.buildMap(currentMap, player1, enemy1, enemy2, enemy3, NPC1, NPC2, NPC3, item1, item2, item3);
        cout << map.printMap(player1) << endl;
        cout << "That ladder was no match for your climbing skills!" << endl;
        break;
    case '!':   // nonPlayer next to character
        switch (y) {
        case 1: // it's NPC1   
            if (NPC1.getNPCType() == "friend") {
                map.mapID[NPC1.getYPosition()][NPC1.getXPosition()] = '_';
                NPC1.setXPosition(0);
                NPC1.setYPosition(0);
                NPC1.setSymbol('|');
                map.buildMap(currentMap, player1, enemy1, enemy2, enemy3, NPC1, NPC2, NPC3, item1, item2, item3);
                cout << map.printMap(player1) << endl;
                NPC1.kind(player1);
                cout << "The stranger ran away into the darkness!" << endl;
            }
            else if (NPC1.getNPCType() == "foe") {
                map.mapID[NPC1.getYPosition()][NPC1.getXPosition()] = '_';
                NPC1.setXPosition(0);
                NPC1.setYPosition(0);
                NPC1.setSymbol('|');
                map.buildMap(currentMap, player1, enemy1, enemy2, enemy3, NPC1, NPC2, NPC3, item1, item2, item3);
                cout << map.printMap(player1) << endl;
                NPC1.curse(player1);
                cout << "The stranger ran away into the darkness!" << endl;
            }
            break;
        case 2: // it's NPC2   
            if (NPC2.getNPCType() == "friend") {
                map.mapID[NPC2.getYPosition()][NPC2.getXPosition()] = '_';
                NPC2.setXPosition(0);
                NPC2.setYPosition(0);
                NPC2.setSymbol('|');
                map.buildMap(currentMap, player1, enemy1, enemy2, enemy3, NPC1, NPC2, NPC3, item1, item2, item3);
                cout << map.printMap(player1) << endl;
                NPC2.kind(player1);
                cout << "The stranger ran away into the darkness!" << endl;
            }
            else if (NPC2.getNPCType() == "foe") {
                map.mapID[NPC2.getYPosition()][NPC2.getXPosition()] = '_';
                NPC2.setXPosition(0);
                NPC2.setYPosition(0);
                NPC2.setSymbol('|');
                map.buildMap(currentMap, player1, enemy1, enemy2, enemy3, NPC1, NPC2, NPC3, item1, item2, item3);
                cout << map.printMap(player1) << endl;
                NPC2.curse(player1);
                cout << "The stranger ran away into the darkness!" << endl;
            }
            break;
        case 3: // it's NPC3   
            if (NPC3.getNPCType() == "friend") {
                map.mapID[NPC3.getYPosition()][NPC3.getXPosition()] = '_';
                NPC3.setXPosition(0);
                NPC3.setYPosition(0);
                NPC3.setSymbol('|');
                map.buildMap(currentMap, player1, enemy1, enemy2, enemy3, NPC1, NPC2, NPC3, item1, item2, item3);
                cout << map.printMap(player1) << endl;
                NPC3.kind(player1);
                cout << "The stranger ran away into the darkness!" << endl;
            }
            else if (NPC3.getNPCType() == "foe") {
                map.mapID[NPC3.getYPosition()][NPC3.getXPosition()] = '_';
                NPC3.setXPosition(0);
                NPC3.setYPosition(0);
                NPC3.setSymbol('|');
                map.buildMap(currentMap, player1, enemy1, enemy2, enemy3, NPC1, NPC2, NPC3, item1, item2, item3);
                cout << map.printMap(player1) << endl;
                NPC3.curse(player1);
                cout << "The stranger ran away into the darkness!" << endl;
            }
            break;
        }

        break;
    case 'X':   // enemy next to character
        switch (y) {
        case 1: // it's enemy1   

            while (player1.getHealth() > 0 && enemy1.getHealth() > 0) {
                // set random seed
                srand(time(NULL));
                // roll the dice
                int diceRoll = rand() % 6 + 1;  // enemy hit
                // calculate the hit
                int hit = enemy1.getStrength() + diceRoll;
                player1.setHealth(player1.getHealth() - hit);
                cout << "The " << enemy1.getName() << " hits the player for " << hit << " damage!" << endl;
                cout << "The player's health is now " << player1.getHealth() << endl;
                this_thread::sleep_for(chrono::seconds(2));

                diceRoll = rand() % 6 + 1;  // player hit
                hit = player1.getStrength() + diceRoll;
                enemy1.setHealth(enemy1.getHealth() - hit);
                cout << "You" << " hit the enemy for " << hit << " damage!" << endl;
                cout << "The enemy's health is now " << enemy1.getHealth() << endl;
                this_thread::sleep_for(chrono::seconds(2));
            }

            if (player1.getHealth() <= 0) {
                cout << "You were defeated in battle!" << endl;
                playing = false;
            }
            else {
                cout << "You defeated the evil monster!" << endl;
                this_thread::sleep_for(chrono::seconds(2));
            }

            map.mapID[enemy1.getYPosition()][enemy1.getXPosition()] = '_';
            enemy1.setXPosition(0);
            enemy1.setYPosition(0);
            enemy1.setSymbol('|');
            map.buildMap(currentMap, player1, enemy1, enemy2, enemy3, NPC1, NPC2, NPC3, item1, item2, item3);
            cout << map.printMap(player1) << endl;
            cout << "Your journey continues..." << endl;

            break;
        case 2: // it's enemy2  

            while (player1.getHealth() > 0 && enemy2.getHealth() > 0) {
                // set random seed
                srand(time(NULL));
                // roll the dice
                int diceRoll = rand() % 6 + 1;  // enemy hit
                // calculate the hit
                int hit = enemy2.getStrength() + diceRoll;
                player1.setHealth(player1.getHealth() - hit);
                cout << "The " << enemy2.getName() << " hits the player for " << hit << " damage!" << endl;
                cout << "The player's health is now " << player1.getHealth() << endl;
                this_thread::sleep_for(chrono::seconds(2));

                diceRoll = rand() % 6 + 1;  // player hit
                hit = player1.getStrength() + diceRoll;
                enemy2.setHealth(enemy2.getHealth() - hit);
                cout << "You" << " hit the enemy for " << hit << " damage!" << endl;
                cout << "The enemy's health is now " << enemy2.getHealth() << endl;
                this_thread::sleep_for(chrono::seconds(2));
            }

            if (player1.getHealth() <= 0) {
                cout << "You were defeated in battle!" << endl;
                playing = false;
            }
            else {
                cout << "You defeated the evil monster!" << endl;
                this_thread::sleep_for(chrono::seconds(2));
            }

            map.mapID[enemy2.getYPosition()][enemy2.getXPosition()] = '_';
            enemy2.setXPosition(0);
            enemy2.setYPosition(0);
            enemy2.setSymbol('|');
            map.buildMap(currentMap, player1, enemy1, enemy2, enemy3, NPC1, NPC2, NPC3, item1, item2, item3);
            cout << map.printMap(player1) << endl;
            cout << "Your journey continues..." << endl;

            break;
        case 3: // it's enemy3   
            
            while (player1.getHealth() > 0 && enemy3.getHealth() > 0) {
                // set random seed
                srand(time(NULL));
                // roll the dice
                int diceRoll = rand() % 6 + 1;  // enemy hit
                // calculate the hit
                int hit = enemy3.getStrength() + diceRoll;
                player1.setHealth(player1.getHealth() - hit);
                cout << "The " << enemy3.getName() << " hits the player for " << hit << " damage!" << endl;
                cout << "The player's health is now " << player1.getHealth() << endl;
                this_thread::sleep_for(chrono::seconds(2));

                diceRoll = rand() % 6 + 1;  // player hit
                hit = player1.getStrength() + diceRoll;
                enemy3.setHealth(enemy3.getHealth() - hit);
                cout << "You" << " hit the enemy for " << hit << " damage!" << endl;
                cout << "The enemy's health is now " << enemy3.getHealth() << endl;
                this_thread::sleep_for(chrono::seconds(2));
            }

            if (player1.getHealth() <= 0) {
                cout << "You were defeated in battle!" << endl;
                playing = false;
                
            }
            else {
                cout << "You defeated the evil monster!" << endl;
                this_thread::sleep_for(chrono::seconds(2));
            }

            map.mapID[enemy3.getYPosition()][enemy3.getXPosition()] = '_';
            enemy3.setXPosition(0);
            enemy3.setYPosition(0);
            enemy3.setSymbol('|');
            map.buildMap(currentMap, player1, enemy1, enemy2, enemy3, NPC1, NPC2, NPC3, item1, item2, item3);
            cout << map.printMap(player1) << endl;
            
            break;
        }

        break;
     case '=':
         switch (y) {
         case 1: // item1

             map.mapID[item1.getYPosition()][item1.getXPosition()] = '_';
             item1.setXPosition(0);
             item1.setYPosition(0);
             item1.setSymbol('|');
             map.buildMap(currentMap, player1, enemy1, enemy2, enemy3, NPC1, NPC2, NPC3, item1, item2, item3);
             cout << map.printMap(player1) << endl;
             player1.recieveItem(player1, item1);
             cout << "Your journey continues..." << endl;

             break;
         
         case 2: // item2

             map.mapID[item2.getYPosition()][item2.getXPosition()] = '_';
             item2.setXPosition(0);
             item2.setYPosition(0);
             item2.setSymbol('|');
             map.buildMap(currentMap, player1, enemy1, enemy2, enemy3, NPC1, NPC2, NPC3, item1, item2, item3);
             cout << map.printMap(player1) << endl;
             player1.recieveItem(player1, item2);
             cout << "Your journey continues..." << endl;

         break;
         case 3: // item3

             map.mapID[item3.getYPosition()][item3.getXPosition()] = '_';
             item3.setXPosition(0);
             item3.setYPosition(0);
             item3.setSymbol('|');
             map.buildMap(currentMap, player1, enemy1, enemy2, enemy3, NPC1, NPC2, NPC3, item1, item2, item3);
             cout << map.printMap(player1) << endl;
             player1.recieveItem(player1, item3);
             cout << "Your journey continues..." << endl;

             break;
         }
         break;
    }

}

void move(playMap& map) {

    direction = "";
    inputRecieved = false;
    moveFinished = false;
    map.player1TileMover = '_';
    map.enemy1TileMover = '_';
    map.enemy2TileMover = '_';
    map.enemy3TileMover = '_';
    
    while (!moveFinished) {

        // If the player is against an Eastern wall with open space on the West side.
        if (map.mapID[player1.getYPosition()][player1.getXPosition() - 1] == "_"
            && map.mapID[player1.getYPosition()][player1.getXPosition() + 1] == "|") {

            cout << "You are up against a wall. The only direction you can move is West. Type 'West' to move." << endl;

            // Handle incorrect input
            do {
                try {
                    cin >> direction;
                    if (direction == "West" || direction == "west" || direction == "w" || direction == "W") {
                        inputRecieved = true;
                    }
                    else {
                        throw direction;
                    }
                }
                catch (string direction) {
                    cout << "You have entered incorrect input. Please type 'West' to continue." << endl;
                }
            } while (!inputRecieved);

            // Move according to input and replace tile that player was standing on
            map.mapID[player1.getYPosition()][player1.getXPosition()] = map.player1TileMover;
            player1.setXPosition(player1.getXPosition() - 1);
            map.buildMap(currentMap, player1, enemy1, enemy2, enemy3, NPC1, NPC2, NPC3, item1, item2, item3);
            cout << map.printMap(player1) << endl;

            // Notify player of move success
            cout << "Moved one space West." << endl;

            // End Move Sequence
            moveFinished = true;
        }

        // If the player is against an Eastern ladder with open space on the West side.
        else if (map.mapID[player1.getYPosition()][player1.getXPosition() - 1] == "_"
            && map.mapID[player1.getYPosition()][player1.getXPosition() + 1] == "<") {

            cout << "There is a ladder to the East. You can use the ladder or go West. Type 'West' or 'Climb.'" << endl;

            // Handle incorrect input
            do {
                try {
                    cin >> direction;
                    if (direction == "West" || direction == "west" || direction == "w" || direction == "W"
                        || direction == "Climb" || direction == "climb" || direction == "c" || direction == "C") {
                        inputRecieved = true;
                    }
                    else {
                        throw direction;
                    }
                }
                catch (string direction) {
                    cout << "You have entered incorrect input. Please type 'West' or 'Climb' to continue." << endl;
                }
            } while (!inputRecieved);

            // Move according to input and replace tile that player was standing on
            if (direction == "West" || direction == "west" || direction == "w" || direction == "W") {
                map.mapID[player1.getYPosition()][player1.getXPosition()] = map.player1TileMover;
                player1.setXPosition(player1.getXPosition() - 1);
                map.buildMap(currentMap, player1, enemy1, enemy2, enemy3, NPC1, NPC2, NPC3, item1, item2, item3);
                cout << map.printMap(player1) << endl;

                // Notify player of move success
                cout << "Moved one space West." << endl;
            }

            if (direction == "Climb" || direction == "climb" || direction == "c" || direction == "C") {
                special(map);
            }

            // End Move Sequence
            moveFinished = true;
        }

        // If the player is against an Western wall with open space on the East side.
        else if (map.mapID[player1.getYPosition()][player1.getXPosition() - 1] == "|"
            && map.mapID[player1.getYPosition()][player1.getXPosition() + 1] == "_") {

            cout << "You are up against a wall. The only direction you can move is East. Type 'East' to move." << endl;

            // Handle incorrect input
            do {
                try {
                    cin >> direction;
                    if (direction == "East" || direction == "east" || direction == "e" || direction == "E") {
                        inputRecieved = true;
                    }
                    else {
                        throw direction;
                    }
                }
                catch (string direction) {
                    cout << "You have entered incorrect input. Please type 'East' to continue." << endl;
                }
            } while (!inputRecieved);

            // Move according to input and replace tile that player was standing on
            map.mapID[player1.getYPosition()][player1.getXPosition()] = map.player1TileMover;
            player1.setXPosition(player1.getXPosition() + 1);
            map.buildMap(currentMap, player1, enemy1, enemy2, enemy3, NPC1, NPC2, NPC3, item1, item2, item3);
            cout << map.printMap(player1) << endl;

            // Notify player of move success
            cout << "Moved one space East." << endl;

            // End Move Sequence
            moveFinished = true;
        }

        // If the player is against an Western ladder with open space on the East side.
        if (map.mapID[player1.getYPosition()][player1.getXPosition() - 1] == ">"
            && map.mapID[player1.getYPosition()][player1.getXPosition() + 1] == "_") {

            cout << "There is a ladder to the West. You can use the ladder or go East. Type 'East' or 'Climb.'" << endl;

            // Handle incorrect input
            do {
                try {
                    cin >> direction;
                    if (direction == "East" || direction == "east" || direction == "e" || direction == "E"
                        || direction == "Climb" || direction == "climb" || direction == "c" || direction == "C") {
                        inputRecieved = true;
                    }
                    else {
                        throw direction;
                    }
                }
                catch (string direction) {
                    cout << "You have entered incorrect input. Please type 'East' or 'Climb' to continue." << endl;
                }
            } while (!inputRecieved);

            // Move according to input and replace tile that player was standing on
            if (direction == "East" || direction == "east" || direction == "e" || direction == "E") {
                map.mapID[player1.getYPosition()][player1.getXPosition()] = map.player1TileMover;
                player1.setXPosition(player1.getXPosition() + 1);
                map.buildMap(currentMap, player1, enemy1, enemy2, enemy3, NPC1, NPC2, NPC3, item1, item2, item3);
                cout << map.printMap(player1) << endl;

                // Notify player of move success
                cout << "Moved one space East." << endl;
            }

            if (direction == "Climb" || direction == "climb" || direction == "c" || direction == "C") {
                special(map);
            }

            // End Move Sequence
            moveFinished = true;
        }

        // If the player is against no wall with open space on the East and West side.  
        else if (map.mapID[player1.getYPosition()][player1.getXPosition() - 1] == "_"
            && map.mapID[player1.getYPosition()][player1.getXPosition() + 1] == "_") {

            cout << "You may move East or West along the platform. Type a direction to move." << endl;

            // Handle incorrect input
            do {
                try {
                    cin >> direction;
                    if (direction == "East" || direction == "east" || direction == "West" || direction == "west"
                        || direction == "w" || direction == "W" || direction == "e" || direction == "E") {
                        inputRecieved = true;
                    }
                    else {
                        throw direction;
                    }
                }
                catch (string direction) {
                    cout << "You have entered incorrect input. Please type 'East' or 'West' to continue." << endl;
                }
            } while (!inputRecieved);

            // Move according to input and replace tile that player was standing on
            if (direction == "East" || direction == "east" || direction == "e" || direction == "E") {
                map.mapID[player1.getYPosition()][player1.getXPosition()] = map.player1TileMover;
                player1.setXPosition(player1.getXPosition() + 1);
                map.buildMap(currentMap, player1, enemy1, enemy2, enemy3, NPC1, NPC2, NPC3, item1, item2, item3);
                cout << map.printMap(player1) << endl;

                // Notify player of move success
                cout << "Moved one space East." << endl;
            }
            else if (direction == "West" || direction == "west" || direction == "w" || direction == "W") {
                map.mapID[player1.getYPosition()][player1.getXPosition()] = map.player1TileMover;
                player1.setXPosition(player1.getXPosition() - 1);
                map.buildMap(currentMap, player1, enemy1, enemy2, enemy3, NPC1, NPC2, NPC3, item1, item2, item3);
                cout << map.printMap(player1) << endl;

                // Notify player of move success
                cout << "Moved one space West." << endl;
            }

            // End Move Sequence
            moveFinished = true;
        }

        // If the player is against an Eastern nonPlayer with open space on the West side.
        else if (map.mapID[player1.getYPosition()][player1.getXPosition() - 1] == "_"
            && map.mapID[player1.getYPosition()][player1.getXPosition() + 1] == "!") {

            cout << "There is a mysterious stranger to the East! You can speak to them or go West. Type 'West' or 'Speak.'" << endl;

            // Handle incorrect input
            do {
                try {
                    cin >> direction;
                    if (direction == "West" || direction == "west" || direction == "w" || direction == "W"
                        || direction == "Speak" || direction == "speak" || direction == "s" || direction == "S") {
                        inputRecieved = true;
                    }
                    else {
                        throw direction;
                    }
                }
                catch (string direction) {
                    cout << "You have entered incorrect input. Please type 'West' or 'Speak' to continue." << endl;
                }
            } while (!inputRecieved);

            // Move according to input and replace tile that player was standing on
            if (direction == "West" || direction == "west" || direction == "w" || direction == "W") {
                map.mapID[player1.getYPosition()][player1.getXPosition()] = map.player1TileMover;
                player1.setXPosition(player1.getXPosition() - 1);
                map.buildMap(currentMap, player1, enemy1, enemy2, enemy3, NPC1, NPC2, NPC3, item1, item2, item3);
                cout << map.printMap(player1) << endl;

                // Notify player of move success
                cout << "Moved one space West." << endl;
            }

            if (direction == "Speak" || direction == "speak" || direction == "s" || direction == "S") {
                special(map);
            }

            // End Move Sequence
            moveFinished = true;
        }

        // If the player is against an Western nonPlayer with open space on the West side.
        else if (map.mapID[player1.getYPosition()][player1.getXPosition() - 1] == "!"
        && map.mapID[player1.getYPosition()][player1.getXPosition() + 1] == "_") {

        cout << "There is a mysterious stranger to the West! You can speak to them or go East. Type 'East' or 'Speak.'" << endl;

        // Handle incorrect input
        do {
            try {
                cin >> direction;
                if (direction == "East" || direction == "east" || direction == "e" || direction == "E"
                    || direction == "Speak" || direction == "speak" || direction == "s" || direction == "S") {
                    inputRecieved = true;
                }
                else {
                    throw direction;
                }
            }
            catch (string direction) {
                cout << "You have entered incorrect input. Please type 'East' or 'Speak' to continue." << endl;
            }
        } while (!inputRecieved);

        // Move according to input and replace tile that player was standing on
        if (direction == "East" || direction == "east" || direction == "e" || direction == "E") {
            map.mapID[player1.getYPosition()][player1.getXPosition()] = map.player1TileMover;
            player1.setXPosition(player1.getXPosition() + 1);
            map.buildMap(currentMap, player1, enemy1, enemy2, enemy3, NPC1, NPC2, NPC3, item1, item2, item3);
            cout << map.printMap(player1) << endl;

            // Notify player of move success
            cout << "Moved one space West." << endl;
        }

        if (direction == "Speak" || direction == "speak" || direction == "s" || direction == "S") {
            special(map);
        }

        // End Move Sequence
        moveFinished = true;
        }

        // If the player is against an enemy battle automatically begins.
        else if (map.mapID[player1.getYPosition()][player1.getXPosition() - 1] == "X"
        || map.mapID[player1.getYPosition()][player1.getXPosition() + 1] == "X") {

        cout << "There is a vicious enemy nearby! Prepare for battle!" << endl;
        this_thread::sleep_for(chrono::seconds(2));

        special(map);

        // End Move Sequence
        moveFinished = true;
        }

        // If the player is against an item the player automatically picks it up.
        else if (map.mapID[player1.getYPosition()][player1.getXPosition() - 1] == "="
        || map.mapID[player1.getYPosition()][player1.getXPosition() + 1] == "=") {

        cout << "You found something in a dark corner of the room..." << endl;
        this_thread::sleep_for(chrono::seconds(2));

        special(map);

        // End Move Sequence
        moveFinished = true;
        }

        // If the player is against the goal, the level is complete!
        else if (map.mapID[player1.getYPosition()][player1.getXPosition() - 1] == "G"
        || map.mapID[player1.getYPosition()][player1.getXPosition() + 1] == "G") {

        map.mapID[0][7] = 'A';
        map.mapID[0][8] = 'L';
        map.buildMap(currentMap, player1, enemy1, enemy2, enemy3, NPC1, NPC2, NPC3, item1, item2, item3);
        cout << map.printMap(player1) << endl;

        cout << "The level is complete!!" << endl;
        this_thread::sleep_for(chrono::seconds(2));
        playing = false;

        // End Move Sequence
        moveFinished = true;
        }
    }

}

void level1() {

    map1.mapPositions(1, player1, enemy1, enemy2, enemy3, NPC1, NPC2, NPC3, item1, item2, item3);
    map1.buildMap(currentMap, player1, enemy1, enemy2, enemy3, NPC1, NPC2, NPC3, item1, item2, item3);

    cout << map1.printMap(player1) << endl;

    // level 1 loop
    while (playing) {
        move(map1);
    }

}

void level2() {

    currentMap = "2";
    map2.mapPositions(2, player1, enemy1, enemy2, enemy3, NPC1, NPC2, NPC3, item1, item2, item3);
    map2.buildMap(currentMap, player1, enemy1, enemy2, enemy3, NPC1, NPC2, NPC3, item1, item2, item3);

    cout << map2.printMap(player1) << endl;

    // level 2 loop
    while (playing) {
        move(map2);
    }

}

void level3() {

    currentMap = "3";
    map3.mapPositions(3, player1, enemy1, enemy2, enemy3, NPC1, NPC2, NPC3, item1, item2, item3);
    map3.buildMap(currentMap, player1, enemy1, enemy2, enemy3, NPC1, NPC2, NPC3, item1, item2, item3);

    cout << map3.printMap(player1) << endl;

    // level 3 loop
    while (playing) {
        move(map3);
    }

}

int main()
{
    
    cout << "You are walking home and you decide to take a shortcut down a dark alley." << endl;
    this_thread::sleep_for(chrono::seconds(3));
    cout << "Suddenly, the ground cracks beneath you and you begin to fall in complete darkness." << endl;
    this_thread::sleep_for(chrono::seconds(3));
    cout << "You brace yourself for pain, but instead you fall into a deep sleep." << endl;
    this_thread::sleep_for(chrono::seconds(3));
    cout << "..." << endl;
    this_thread::sleep_for(chrono::seconds(3));
    cout << "You wake up feeling hungry in a small dark room. In the distance, you can make out a ladder." << endl;
    this_thread::sleep_for(chrono::seconds(3));
    cout << "You can move and perform actions by typing the action, or the letter it starts with, in the console." << endl;
    this_thread::sleep_for(chrono::seconds(3));
    cout << "Welcome to Crazy Maze." << endl;
    this_thread::sleep_for(chrono::seconds(3)); 
    
    level1();
    
    playing = true; 
    level2();
    
    playing = true; 
    level3();

    cout << "You emerge victorious from the dark maze!" << endl;
    this_thread::sleep_for(chrono::seconds(3));
    cout << "As you look at your reflection in a nearby shop window..." << endl;
    this_thread::sleep_for(chrono::seconds(3));
    cout << "You notice that all of your items are gone and you are now in your regular clothes." << endl;
    this_thread::sleep_for(chrono::seconds(3));
    cout << "..." << endl;
    this_thread::sleep_for(chrono::seconds(3));
    cout << "You make your way home trying to remember what happened so that you can tell someone... anyone..." << endl;
    this_thread::sleep_for(chrono::seconds(3));
    cout << "Before long, the memory fades and becomes more like a dream..." << endl;
    this_thread::sleep_for(chrono::seconds(3));
    cout << "But you know that no matter how distant the memory becomes, you will always remember Crazy Maze." << endl;
    this_thread::sleep_for(chrono::seconds(3));

}

