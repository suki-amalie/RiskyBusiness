//
// Created by ADMIN on 16-Sep-23.
//

#include "Bronze.h"


Bronze::Bronze(string name) : Company(name) {
    Company::setSharePrice(rand()%(level + 4) + 1); //randomise share price from 1 to level + 4
    Company::setCompanyCost(2*5*level);
}

void Bronze::usePower(Player &player) {
    int multiplier = rand() % mode + 2;
    cout << "Added $" << 10 * mode * multiplier << " to " << player.getPlayerName() << "'s account\n";
    player.updateMoney(10 * mode * multiplier);
}