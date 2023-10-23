/**************************************************
 Project: Risky Business - Assigment 2 part B
 Author: Jash Nguyen
 Purpose: SILVER COMPANY CLASS Header file
**************************************************/

#ifndef A2_JASHNGUYEN_SILVER_H
#define A2_JASHNGUYEN_SILVER_H
#include "Company.h"

class Silver: public Company{
private:
    int level = 4;
    string power = "shares";

public:
    Silver();
    Silver(string name);
    string getDetails();
    string getPower();
    int getLevel();

};


#endif //A2_JASHNGUYEN_SILVER_H
