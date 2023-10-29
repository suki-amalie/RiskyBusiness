/**************************************************
 Project: Risky Business - Assigment 2 part B
 Author: Jash Nguyen (34327681)
 Purpose: GameAdvanced class header file
**************************************************/

#ifndef A2_JASHNGUYEN_GAMEADVANCED_H
#define A2_JASHNGUYEN_GAMEADVANCED_H

#include "GameDefault.h"
using  namespace std;

class GameAdvanced: public GameDefault {
public:
    /************************* CONSTRUCTORS *********************/
    GameAdvanced();
    GameAdvanced(int newGameMode, int playerNum, int currentDay);

    /********************** GAME FUNCTIONS **********************/
    void checkMenuSelection(char userChoice, Player& player);
    void acquireCompany(Player & player);
    void mergeCompany(Player & player);
    bool haveAnotherShareHolder(char companyKey, string playerName);
    bool fileExist(string fileName);
    void saveGame(string inputFile);
    void loadGame(string outputFile);
    /*************** DISPLAY FUNCTION **********************/
    void displayMenu();

};


#endif //A2_JASHNGUYEN_GAMEADVANCED_H
