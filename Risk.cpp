/**************************************************
 Project: Risky Business - Assigment 2 part B
 Author: Jash Nguyen (34327681)
 Purpose: RISK CLASS file
**************************************************/
#include "Risk.h"

/********************* CONSTRUCTOR FUNCTIONS *********************/
/*Default constructor*/
Risk::Risk() {
    setRiskName("");
    setRiskEffect("");
    setMaximum(0);
    setMaximum(0);
}

/*Overloaded constructor*/
Risk::Risk(string newName, string newEffect, int min, int max) {
    setRiskName(newName);
    setRiskEffect(newEffect);
    setMinimum(min);
    setMaximum(max);
}

/********************* ACCESSOR FUNCTIONS *********************/


string Risk::getName() {
    return riskName;
}

string Risk::getEffect() {
    return riskEffect;
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

/********************* MUTATOR FUNCTIONS *********************/
void Risk::setRiskName(string name) {
    riskName = name;
}

void Risk::setRiskEffect(string effect) {
    riskEffect = effect;
}

void Risk::setMaximum(int max) {
    maximum = max;
}

void Risk::setMinimum(int min) {
    minimum = min;
}



