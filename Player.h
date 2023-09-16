//
// Created by ADMIN on 08-Sep-23.
//

#ifndef A2_JASHNGUYEN_PLAYER_H
#define A2_JASHNGUYEN_PLAYER_H


#include <string>
#include <vector>
#include <algorithm>
#include "Company.h"
#include "sstream"
#include <map>
using namespace std;

class Player {
private:
    string playerName;
    int money;
    int totalShares;
    int totalCompaniesOwned;
    int gameMode; // Set game difficulty from 1-3
    int powerUsageLeft;
    map<char, int> companiesDetails;  //list of company and its corresponding shares owned by player
public:
    Player();
    Player(string name, int mode);
    ~Player();

    string getPlayerName();
    string getDetails();
    int getMoney();
    int getTotalShares();
    int getTotalCompaniesOwned();
    map<char, int> getCompaniesDetails();
    int getPowerUsageLeft();
    int getSharesinCompany(char companyKey);

    void setMoney(int newAmount);
    void setPowerUsage(int number);
    void updateMoney(int change);
    void setGameMode(int mode);
    void setTotalCompaniesOwned(int amount);
    void setPlayerName(string name);

    void updateTotalShares(int change);
    void updatePowerUsage(int change);
    void updateTotalCompaniesOwned(int change);
    void buyShares(Company & company, int amount);
    void sellShares(Company & company, int amount);

};




#endif //A2_JASHNGUYEN_PLAYER_H
