/**************************************************
 Project: Risky Business - Assigment 2 part B
 Author: Jash Nguyen (34327681)
 Purpose: GAME DEFAULT CLASS Header file
**************************************************/

#ifndef A2_JASHNGUYEN_GAMEDEFAULT_H
#define A2_JASHNGUYEN_GAMEDEFAULT_H


#include "main.h"
#include "Player.h"
#include "Company.h"
#include "Bronze.h"
#include "Silver.h"
#include "Gold.h"
#include "Risk.h"
using namespace std;

class GameDefault {
protected:
    int gameMode;
    int dayCounter;
    int playersNumber;
    vector<Company*> companies;
    vector<Risk> risks;
    vector<Player> players;
    int minCompanies;
    int minMoney;
    int maxDays;
    string divider = string(70, '~');
    string noOwner = "-------";
public:

    /****************** MAIN FUNCTION ******************/
    void playGame();

    /********** CONSTRUCTORS ************/
    GameDefault();
    GameDefault(int newGameMode, int playerNum, int currentDay);

    /************** DESTRUCTOR ************/
    ~GameDefault();

    /************ SETTER FUNCTIONS *********/
    void setGameMode(int val);
    void setDay(int val);
    void setPlayersNumber(int val);
    void setUpCompanies(int maxCompanies, string fileName);
    void setUpShares();
    void setUpRisks(string fileName);
    void setUpPlayers(int mode, int playersNumb);

    /********* GET FUNCTIONS ************************/
    int getIndexFromPlayer(Player player);
    int getCompanyIndex(char companyKey);
    int getMinMoney(int mode);
    int getMaxDays(int mode);
    int getMaxCompanies(int mode);
    int getMinCompanies(int mode);
    int getRandomNum(int min, int max);

    /************* GAME FUNCTIONS ******************/

    void resetSharesPrice();
    void resetGame();
    virtual void checkMenuSelection(char userChoice, Player & player);
    void takeARisk(Player & player);
    virtual void acquireCompany(Player & player);
    char askForCompanyKey(string question);
    void mergeCompany(Player & player);
    void usePower(Player & player);
    void moneyPower(Player &player, int amount);
    void sharePower(Player &player, int amount);
    void moneyEffect(Player & player, int min, int max);
    void shareEffect(Player & player, int min, int max);
    void buyShares(Player & player);
    void sellShares(Player& player);
    void quitPlayer(Player player);

    /*************** DISPLAY FUNCTIONS ************/

    virtual void displayMenu();
    void displayMarket();
    void displayGameInterface(Player player);

};


#endif //A2_JASHNGUYEN_GAMEDEFAULT_H
