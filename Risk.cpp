/**************************************************
 Project: Risky Business - Assigment 2 part B
 Author: Jash Nguyen (34327681)
 Purpose: Risk class application file
**************************************************/

#include "Risk.h"

Risk::Risk() {
    riskName = "";
    effect = "";
    maximum = 0;
    minimum = 0;
}

Risk::Risk(string newName, string newEffect, int min, int max) {
    riskName = newName;
    effect = newEffect;
    minimum = min;
    maximum = max;
}

string Risk::getName() {
    return riskName;
}

string Risk::getEffect() {
    return effect;
}
int Risk::getMax() {
    return maximum;
}

int Risk::getMin() {
    return minimum;
}

string Risk::getDetails() {
    stringstream riskDetails;
    riskDetails << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
    riskDetails << "\n Risk Name: " << getName();
    // add code here for displaying the rank name and score
    riskDetails << "\n Effect: " << getEffect();
    riskDetails << "\n Minimum: " << getMin();
    riskDetails << "\n Maximum: " << getMax() << endl;
    return riskDetails.str();
}



