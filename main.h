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
#include "Risk.h"
using namespace std;

vector<Company> companies;
vector<Risk> risks;
vector<Player> players;
vector<char> menuOptions = {'B', 'S', 'A', 'P', 'R', 'Q'};
string divider = string(80, '~');
int numberOfPlayers = 1;
int dayCounter = 1;
bool won = false;
string noOwner = "-------";

int askForNumber(string question, int min, int max);
int getIndexFromPlayer(Player player);
int getIndexFromCompanyKey(char key);
int askForCompanyKey(string question);
string askForString(string question);
char askForLetter(string question);
void testPlayer();
void testCompany();
void testRisk();
void setUpPlayer();
void quitPlayer(Player player);
void displayPlayerPortfolio(Player player);
void setUpGame();
void playGame(Player & player);
void parseCompanyData();
void displayCompanies();
Company getCompanyByKey(char key);
string listCompanyKeys();
void displayMenu();
void parseRiskData();
void action(char userChoice, Player & player);
void displayRisks();
void takeARisk(Player & player);
void acquireCompany(Player & player);
void usePower(Player & player);
void calculateMoneyEffect(Player & player, int min, int max);
void calculateShareEffect(Player & player, int min, int max);
void waitForPlayer();
void clearScreen();
void displayTitle();
void displayTextFile(string myFile);
void displayGameStatus();
void displayMarket();
int generateRandomNum(int min, int max);

#endif //A2_JASHNGUYEN_MAIN_H
