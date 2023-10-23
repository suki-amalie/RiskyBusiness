/**************************************************
 Project: Risky Business - Assigment 2 part B
 Author: Jash Nguyen
 Purpose: BRONZE COMPANY CLASS Header file
**************************************************/

#ifndef A2_JASHNGUYEN_BRONZE_H
#define A2_JASHNGUYEN_BRONZE_H

#include "Company.h"

class Bronze: public Company{
private:
    int level = 3;
    string power = "money";
public:
    Bronze();
    Bronze(string name);
    string getDetails();
    string getPower();
    int getLevel();
};


#endif //A2_JASHNGUYEN_BRONZE_H
