/**************************************************
 Project: Risky Business - Assigment 2 part B
 Author: Jash Nguyen (34327681)
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
    string riskEffect;
    int maximum;
    int minimum;
public:
    // constructors
    Risk();
    Risk(string newName, string newEffect, int min, int max);

    // destructor
    ~Risk() = default;

    // accessor functions
    string getName();
    string getEffect();
    int getMax();
    int getMin();
    string getDetails();

    //mutator methods
    void setRiskName(string name);
    void setRiskEffect(string effect);
    void setMaximum(int max);
    void setMinimum(int min);
};


#endif //A2_JASHNGUYEN_RISK_H
