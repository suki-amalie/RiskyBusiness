//
// Created by ADMIN on 08-Sep-23.
//

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
    Risk();
    Risk(string newName, string newEffect, int min, int max);
    string getName();
    string getEffect();
    int getMax();
    int getMin();
    string getDetails();
};


#endif //A2_JASHNGUYEN_RISK_H
