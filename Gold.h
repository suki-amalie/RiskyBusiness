/**************************************************
 Project: Risky Business - Assigment 2 part B
 Author: Jash Nguyen (34327681)
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
    Gold(string newName, string newOwner, int newShares, int newSharePrice, int newCost);


    string getDetails();
    string getPower();
    int getLevel();

};


#endif //A2_JASHNGUYEN_GOLD_H
