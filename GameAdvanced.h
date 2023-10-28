//
// Created by ADMIN on 27-Oct-23.
//

#ifndef A2_JASHNGUYEN_GAMEADVANCED_H
#define A2_JASHNGUYEN_GAMEADVANCED_H

#include "GameDefault.h"
using  namespace std;

class GameAdvanced: public GameDefault {
public:
    /********** MAIN FUNCTION ******/
    GameAdvanced();
    GameAdvanced(int newGameMode, int playerNum, int currentDay);
    void checkMenuSelection(char userChoice, Player& player);

    bool haveAnotherShareHolder(char companyKey, string playerName);
    void acquireCompany(Player & player);
    void mergeCompany(Player & player);
    void displayMenu();

    /********************** EXTRA FUNCTIONALITIES ***********************/

    bool fileExist(string fileName);
    void saveGame(string inputFile);
    void loadGame(string outputFile);


};


#endif //A2_JASHNGUYEN_GAMEADVANCED_H
