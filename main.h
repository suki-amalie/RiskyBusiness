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


/******* INPUT FUNCTIONS *************************/

int askForNumber(string question, int min, int max);
string askForString(string question);
char askForLetter(string question);

/*************** DISPLAY FUNCTIONS ************/
void waitForPlayer();
void clearScreen();
void displayTitle();
void displayTextFile(string myFile);

#endif //A2_JASHNGUYEN_MAIN_H
