/**************************************************
 Project: Risky Business - Assigment 2 part B
 Author: Jash Nguyen (34327681)
 Purpose: GameDefault class header file
**************************************************/

#ifndef A2_JASHNGUYEN_GAMEDEFAULT_H
#define A2_JASHNGUYEN_GAMEDEFAULT_H

#include "Player.h"
#include "Company.h"
#include "Bronze.h"
#include "Silver.h"
#include "Gold.h"
#include "Risk.h"
#include "workhorse.h"

using namespace std;

class GameDefault {
protected:
    const int WIDTH = 100;
    int gameMode;
    int dayCounter;
    int playersNumber;
    vector<Company*> companies;
    vector<Risk> risks;
    vector<Player> players;
    int minCompanies;
    int minMoney;
    int maxDays;
    string noOwner = "-------";
public:

    /********** MAIN FUNCTION ******/
    void playGame();

    /********** CONSTRUCTORS ************/
    GameDefault();
    GameDefault(int newGameMode, int playerNum, int currentDay);

    /************** DESTRUCTOR ************/
    ~GameDefault();

    /************ SETTER FUNCTIONS *********/

    void setUpCompanies(int maxCompanies, string fileName);
    void setUpShares();
    void setUpRisks(string fileName);
    void setUpPlayers(int playersNumb);

    /********* GET FUNCTIONS ************************/
    int getIndexFromPlayer(Player player);
    int getCompanyIndex(char companyKey);
    int getMinMoney(int mode);
    int getMaxDays(int mode);
    int getMaxCompanies(int mode);
    int getMinCompanies(int mode);
    int getRandomNum(int min, int max);

    /************ MUTATOR FUNCTIONS ****************/

    void resetSharesPrice();
    void resetGame();

    /************* GAME FUNCTIONS ******************/

    virtual void checkMenuSelection(char userChoice, Player & player);
    void takeARisk(Player & player);
    virtual void acquireCompany(Player & player);
    void usePower(Player & player);
    void moneyPower(Player &player, int amount);
    void sharePower(Player &player, int amount);
    void moneyEffect(Player & player, int min, int max);
    void shareEffect(Player & player, int min, int max);
    void buyShares(Player & player);
    void sellShares(Player& player);
    void quitPlayer(Player player);
    char askForCompanyKey(string question);


    /*************** DISPLAY FUNCTIONS ************/

    void displayTitle();
    virtual void displayMenu();
    void displayMarket();
    void displayGameInterface(Player player);

};


#endif //A2_JASHNGUYEN_GAMEDEFAULT_H
