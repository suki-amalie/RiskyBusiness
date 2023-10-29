/**************************************************
 Project: Risky Business - Assigment 2 part B
 Author: Jash Nguyen (34327681)
 Purpose: main header file
**************************************************/

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


/******* INPUT FUNCTIONS *************************/

int askForNumber(string question, int min, int max);
string askForString(string question);
char askForLetter(string question);

/*************** DISPLAY FUNCTIONS ************/
void waitForPlayer();
void clearScreen();
void displayTextFile(string myFile);
std::string center(const string s, const int w);

#endif //A2_JASHNGUYEN_MAIN_H
