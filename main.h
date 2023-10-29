/**************************************************
 Project: Risky Business - Assigment 2 part B
 Author: Jash Nguyen
 Purpose: MAIN CLASS Header file
**************************************************/

#ifndef A2_JASHNGUYEN_MAIN_H
#define A2_JASHNGUYEN_MAIN_H

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <iomanip>
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
