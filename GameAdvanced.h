/**************************************************
 Project: Risky Business - Assigment 2 part B
 Author: Jash Nguyen (34327681)
 Purpose: GAME ADVANCED CLASS Header file
**************************************************/

#ifndef A2_JASHNGUYEN_GAMEADVANCED_H
#define A2_JASHNGUYEN_GAMEADVANCED_H

#include "GameDefault.h"
using  namespace std;

class GameAdvanced: public GameDefault {
public:
    /********** CONSTRUCTORS ******/
    GameAdvanced();
    GameAdvanced(int newGameMode, int playerNum);

    /************* GAME FUNCTIONS ******************/
    virtual void checkMenuSelection(char userChoice, Player& player);
    bool haveAnotherShareHolder(char companyKey, string playerName);
    virtual void acquireCompany(Player & player);
    void mergeCompany(Player & player);
    bool fileExist(string fileName);
    void saveGame(string inputFile);
    void loadGame(string outputFile);

    /*********** DISPLAY FUNCTIONS ***************/
    void displayMenu();
};


#endif //A2_JASHNGUYEN_GAMEADVANCED_H
