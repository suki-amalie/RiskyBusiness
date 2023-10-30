/**************************************************
 Project: Risky Business - Assigment 2 part B
 Author: Jash Nguyen (34327681)
 Purpose: WORKHORSE Header file
**************************************************/

#ifndef A2_JASHNGUYEN_WORKHORSE_H
#define A2_JASHNGUYEN_WORKHORSE_H
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <iomanip>

using namespace std;

/********************** INPUT FUNCTIONS *************************/

int askForNumber(string question, int min, int max);
string askForString(string question);
char askForLetter(string question);

/*************** DISPLAY FUNCTIONS ************/
void waitForPlayer();
void clearScreen();
void displayTextFile(string myFile);
#endif //A2_JASHNGUYEN_WORKHORSE_H
