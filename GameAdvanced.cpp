//
// Created by ADMIN on 27-Oct-23.
//

#include "GameAdvanced.h"

void GameAdvanced::playGame() {
    GameDefault::playGame();
}

GameAdvanced::GameAdvanced():GameDefault() {

}

GameAdvanced::GameAdvanced(int newGameMode, int playerNum, int currentDay) : GameDefault(newGameMode, playerNum,
                                                                                         currentDay) {

}


