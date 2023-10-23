/**************************************************
 Project: Risky Business - Assigment 2 part B
 Author: Jash Nguyen
 Purpose: GOLD COMPANY CLASS Header file
**************************************************/

#ifndef A2_JASHNGUYEN_GOLD_H
#define A2_JASHNGUYEN_GOLD_H
#include "Company.h"

class Gold: public Company{
private:
    int level = 5;
    string power = "assets";
public:
    Gold();
    Gold(string name);
    string getDetails();
    string getPower();
    int getLevel();

};


#endif //A2_JASHNGUYEN_GOLD_H
