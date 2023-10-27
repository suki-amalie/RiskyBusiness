//
// Created by ADMIN on 26-Oct-23.
//

#ifndef A2_JASHNGUYEN_GAMEDEFAULT_H
#define A2_JASHNGUYEN_GAMEDEFAULT_H


#include "main.h"
using namespace std;

class GameDefault {
private:
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

    /********** MAIN FUNCTION ******/
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
    void setUpPlayers(int mode, int playersNumber);
    void setUpGame(int gameMode);


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

    void checkMenuSelection(char userChoice, Player & player);
    void checkMenuSelectionAdvanced(char userChoice, Player& player, int currentDay);
    void takeARisk(Player & player);
    void acquireCompany(Player & player);
    bool haveAnotherShareHolder(char companyKey, string playerName);
    void acquireCompanyAdvanced(Player & player);

    /***************** INPUT FUNCTION *****************/
    char askForCompanyKey(string question);
    void mergeCompany(Player & player);
    void usePower(Player & player);
    void moneyPower(Player &player, int amount);
    void sharePower(Player &player, int amount);
    void moneyEffect(Player & player, int min, int max);
    void shareEffect(Player & player, int min, int max);
    void buyShares(Player & player);
    void sellShares(Player& player);

    /**************** PLAYER FUNCTIONS *************/
    void quitPlayer(Player player);

    /*************** DISPLAY FUNCTIONS ************/

    void displayMenu();
    void displayMenuAdvanced();
    void displayMarket();
    void displayGameInterface(Player &player, int minCompanies, int minMoney, int day);

    /********************** EXTRA FUNCTIONALITIES ***********************/

    bool fileExist(string fileName);
    void saveGame(string inputFile, int gameMode, int dayCounter);
    void loadGame(string outputFile);
};


#endif //A2_JASHNGUYEN_GAMEDEFAULT_H