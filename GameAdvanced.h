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
    void playGame();

    GameAdvanced();
    GameAdvanced(int newGameMode, int playerNum, int currentDay);


};


#endif //A2_JASHNGUYEN_GAMEADVANCED_H
