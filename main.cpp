/**************************************************
 Project: Risky Business - Assigment 2 part B
 Author: Jash Nguyen (34327681)
 Purpose: Application file
**************************************************/

#include "main.h"


int main() {
    //set up new seed
    GameDefault* bPtr = nullptr;
    GameAdvanced gameAdvanced;
    srand(unsigned (time(nullptr)));

    // default intro
    //displayTextFile("RBintro.txt");

    // advanced intro
    displayTextFile("RBintroAdvanced.txt");

    int gameMode = askForNumber("Enter game difficulty level: ", 4, 6);
    int numberOfPlayers = askForNumber("Enter number of players", 1, 4);

    // Default game play
    //bPtr = new GameDefault(gameMode, numberOfPlayers);

    // Advanced game play
    bPtr = new GameAdvanced(gameMode, numberOfPlayers);

    bPtr->playGame();

    // clean up memory
    delete bPtr;
    return 0;
}

