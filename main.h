//
// Created by ADMIN on 08-Sep-23.
//

#ifndef A2_JASHNGUYEN_MAIN_H
#define A2_JASHNGUYEN_MAIN_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include "Player.h"
#include "Company.h"
#include "Bronze.h"
#include "Silver.h"
#include "Gold.h"
#include "Risk.h"
using namespace std;

vector<Company*> companies;
vector<Risk> risks;
vector<Player> players;
string divider = string(70, '~');
int numberOfPlayers = 1;
string noOwner = "-------";
string options = "BSAPRQ";
/******* INPUT FUNCTIONS *************************/
int askForNumber(string question, int min, int max);
char askForCompanyKey(string question);
string askForString(string question);
char askForLetter(string question);

/********* GET FUNCTIONS ************************/
int getIndexFromPlayer(Player player);
int getCompanyIndex(char companyKey);
int getMinMoney(int mode);
int getMaxDays(int mode);
int getMaxCompanies(int mode);
int getMinCompanies(int mode);
int getRandomNum(int min, int max);
string getCompanyKeys(int mode);

/************ SET UP FUNCTIONS ****************/
void setUpShares();
void setUpPlayers(int mode, int playersNumber);
void setUpGame();
void setUpCompanies(int maxCompanies, string fileName);
void setUpRisks(string fileName);

/************* GAME FUNCTIONS ******************/
void playGame(Player & player);
void checkMenuSelection(char userChoice, Player & player);
void takeARisk(Player & player);
void acquireCompany(Player & player);
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
void waitForPlayer();
void clearScreen();
void displayCompanies();
void displayRisks();
void displayTitle();
void displayTextFile(string myFile);
void displayMarket();
void displayGameInterface(Player &player, int minCompanies, int minMoney, int day);

#endif //A2_JASHNGUYEN_MAIN_H
