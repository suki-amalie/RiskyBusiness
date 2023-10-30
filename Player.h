/**************************************************
 Project: Risky Business - Assigment 2 part B
 Author: Jash Nguyen (34327681)
 Purpose: PLAYER CLASS Header file
**************************************************/

#ifndef A2_JASHNGUYEN_PLAYER_H
#define A2_JASHNGUYEN_PLAYER_H


#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "sstream"
#include <map>
#include "Company.h"

using namespace std;

class Player {
private:
    string playerName;
    int money;
    int totalShares;
    int totalCompaniesOwned;
    int gameMode; // Set game difficulty from 1-3
    int powerUsageLeft;
    bool isActive;
    map<Company*, int> companiesDetails;  //list of company and its corresponding shares owned by player
public:
    // constructors
    Player();
    Player(string name, int mode);
    // destructor
    ~Player()=default;

    // accessor functions
    string getPlayerName();
    string getDetails();
    string getPortfolio();
    int getMoney();
    int getTotalShares();
    int getTotalCompaniesOwned();
    map<Company*, int> getCompaniesDetails();
    int getPowerUsageLeft();
    int getCompanyShares(char companyKey);
    int getMode();
    bool getState();

    // mutator functions
    void setMoney(int newAmount);
    void setPowerUsage(int number);
    void updateMoney(int change);
    void setGameMode(int mode);
    void setTotalCompaniesOwned(int amount);
    void setPlayerName(string name);
    void setActiveState(bool newState);

    void updateTotalShares(int change);
    void updateCompanyShares(Company* ptr, int amount);
    void updatePowerUsage(int change);
    void updateTotalCompaniesOwned(int change);
    void buyShares(Company* ptr, int amount);
    void sellShares(Company* ptr, int amount);

};




#endif //A2_JASHNGUYEN_PLAYER_H
