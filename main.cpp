/**************************************************
 Project: Risky Business - Assigment 2 part B
 Author: Jash Nguyen (34327681)
 Purpose: Application file
**************************************************/

#include "main.h"
#include "workhorse.h"


/*PUT IN HEADER COMMENT FOR HEADER FILES*/
int main() {
    GameDefault* bPtr = nullptr;
    GameAdvanced gameAdvanced;
    //Set up new seed
    srand(unsigned (time(nullptr)));

    //Display intro to game
    displayTextFile("RBintro.txt");

    //Select game mode and players number
    int gameMode = askForNumber("Enter game difficulty level: ", 4, 6);
    int numberOfPlayers = askForNumber("Enter number of players", 1, 3);

    /* I've implemented 2 versions of game, the default one and advanced one with the save,
     * merge options and advanced risks*/

    //Set up default game play
    bPtr = new GameDefault(gameMode, numberOfPlayers, 1);

    //Set up advanced game play
    //bPtr = new GameAdvanced(gameMode, numberOfPlayers, 1);

    bPtr->playGame();

    // delete pointer
    delete bPtr;
    bPtr = nullptr;

    return 0;
}

