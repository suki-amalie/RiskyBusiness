/**************************************************
 Project: Risky Business - Assigment 2 part B
 Author: Jash Nguyen (34327681)
 Purpose: PLAYER CLASS file
**************************************************/

#include "Player.h"

Player::Player() {
    playerName = "";
    totalCompaniesOwned = 0;
    isActive = false;
}

Player::Player(string name, int mode) {
    setPlayerName(name);
    setGameMode(mode);
    setMoney(5*10*gameMode);
    setPowerUsage(10 - gameMode);
    setTotalCompaniesOwned(0);
    totalShares = 0;
    setActiveState(true);
}


int Player::getTotalCompaniesOwned() {
    return totalCompaniesOwned;
}

string Player::getPlayerName() {
    return playerName;
}

int Player::getMoney() {
    return money;
}

int Player::getTotalShares() {
    return totalShares;
}

void Player::setGameMode(int mode) {
    gameMode = mode;
}

void Player::setPlayerName(string name) {
    playerName = name != "" ? name: "NONE";

}

void Player::setActiveState(bool newState) {
    isActive = newState;
}

void Player::setMoney(int newAmount) {
    money = newAmount;
}

void Player::setTotalCompaniesOwned(int amount) {
    totalCompaniesOwned = amount;
}

int Player::getPowerUsageLeft() {
    return powerUsageLeft;
}

string Player::getDetails() {
    stringstream playerDetails;
    playerDetails << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
    playerDetails << "\n Player Name: " << playerName;
    playerDetails << "\n Game mode: " << gameMode;
    playerDetails << "\n Available money: " << money;
    playerDetails << "\n Power usage left: " << powerUsageLeft;
    playerDetails << "\n Total Companies Owned: " << totalCompaniesOwned;
    playerDetails << "\n Total Shares Owned: " << totalShares << endl;
    return playerDetails.str();
}

void Player::updateMoney(int change) {
    money += change;
}

void Player::updateTotalShares(int change) {
    totalShares += change;
}

void Player::buyShares(Company* ptr, int amount) {
    updateCompanyShares(ptr, amount);
    updateTotalShares(amount);
    updateMoney(-1*amount*ptr->getSharePrice());
    // decrease company shares
    ptr->updateShares(-amount);
}

map<Company*, int> Player::getCompaniesDetails() {
    return companiesDetails;
}

void Player::sellShares(Company* ptr, int amount) {
    // decrease player's shares in company by sell amount
    companiesDetails[ptr] -= amount;
    // increase company's total available shares
    ptr->updateShares(amount);
    // decrease player's total shares
    updateTotalShares(-1*amount);
    // increase player's money
    updateMoney(amount*ptr->getSharePrice());
    // remove company from player's companies if company is not owned by player and
    // player has no shares in company
    if (companiesDetails[ptr] <= 0 && ptr->getOwnerName() != playerName) {
        companiesDetails.erase(ptr); //remove company pointer from player's companies
    }
}

void Player::updatePowerUsage(int change) {
    powerUsageLeft += change;
}

void Player::updateTotalCompaniesOwned(int change) {
    totalCompaniesOwned += change;
}

int Player::getCompanyShares(char companyKey) {
    for (auto pair:companiesDetails) {
        if (pair.first -> getKey() == companyKey) {
            return pair.second;
        }
    }
    return 0;
}

void Player::setPowerUsage(int number) {
    powerUsageLeft = number;
}

string Player::getPortfolio() {
    stringstream portfolio;
    portfolio << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    portfolio << setw(35) << getPlayerName() << "'s Share Portfolio and Assets\n";
    portfolio << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    portfolio << setw(30) << "Total money: $" << money << setw(20) << "Companies Owned: "
    << totalCompaniesOwned << setw(20) << "Total Shares: " << totalShares <<
    setw(12) << "Power: " << getPowerUsageLeft() << "\n";
    if (getCompaniesDetails().size() > 0) {
        portfolio << setw(40) << "Company Names" << setw(21) << "Shares" << setw(15) << "Power" << endl;
        for (auto companyShare: getCompaniesDetails()) {
            Company* companyPtr = companyShare.first;
            int shares = companyShare.second;
            string power = (companyPtr->getOwnerName() == getPlayerName()) ? companyPtr->getPower() : "None";
            portfolio << setw(48) << companyPtr->getCompanyName() << setw(11) << shares << setw(16) << power << "\n";
        }
    } else
    {
        portfolio << setw(70) << "Your share portfolio is empty, " << getPlayerName() << endl;
    }
    return portfolio.str();
}

int Player::getMode() {
    return gameMode;
}

bool Player::getState() {
    return isActive;
}

void Player::updateCompanyShares(Company *ptr, int amount) {
    if (companiesDetails.find(ptr) != companiesDetails.end()) {
        companiesDetails[ptr] += amount;
    } else
    {
        companiesDetails[ptr] = amount;
    }
}





