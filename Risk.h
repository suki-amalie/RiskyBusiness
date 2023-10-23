/**************************************************
 Project: Risky Business - Assigment 2 part B
 Author: Jash Nguyen
 Purpose: RISK CLASS Header file
**************************************************/

#ifndef A2_JASHNGUYEN_RISK_H
#define A2_JASHNGUYEN_RISK_H
#include <string>
#include <sstream>
using namespace std;

class Risk {
private:
    string riskName;
    string effect;
    int maximum;
    int minimum;
public:
    // constructors
    Risk();
    Risk(string newName, string newEffect, int min, int max);

    // accessor functions
    string getName();
    string getEffect();
    int getMax();
    int getMin();
    string getDetails();
};


#endif //A2_JASHNGUYEN_RISK_H
