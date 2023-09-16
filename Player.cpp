//
// Created by ADMIN on 08-Sep-23.
//

#include "Player.h"
Player::Player() {
    playerName = "";
    totalCompaniesOwned = 0;
}

Player::Player(string name, int mode) {
    setPlayerName(name);
    setGameMode(mode);
    setMoney(5*10*gameMode);
    setPowerUsage(10 - gameMode);
    setTotalCompaniesOwned(0);
    totalShares = 0;
}

Player::~Player() {

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
    playerName = name;

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

void Player::buyShares(Company & company, int amount) {
    char companyKey = company.getKey();
    if (companiesDetails.find(companyKey) != companiesDetails.end()) {
        companiesDetails[companyKey] += amount;
    } else
    {
        companiesDetails[companyKey] = amount;
    }
    updateTotalShares(amount);
    company.updateShares(-1*amount);
    updateMoney(-1*amount*company.getSharePrice());
}

map<char, int> Player::getCompaniesDetails() {
    return companiesDetails;
}

void Player::sellShares(Company & company, int amount) {
    char companyKey = company.getKey();
    companiesDetails[companyKey] -= amount;
    if (companiesDetails[companyKey] <= 0 && company.getOwnerName() != playerName) {
        companiesDetails.erase(companyKey);
    }
    company.updateShares(amount);
    updateTotalShares(-1*amount);
    updateMoney(amount*company.getSharePrice());
}

void Player::updatePowerUsage(int change) {
    powerUsageLeft += change;
}

void Player::updateTotalCompaniesOwned(int change) {
    totalCompaniesOwned += change;
}


int Player::getSharesinCompany(char companyKey) {
    if (companiesDetails.find(companyKey) != companiesDetails.end()) {
        return companiesDetails[companyKey];
    } else
    {
        return 0;
    }
}

void Player::setPowerUsage(int number) {
    powerUsageLeft = number;
}





