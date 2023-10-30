/**************************************************
 Project: Risky Business - Assigment 2 part B
 Author: Jash Nguyen (34327681)
 Purpose: BASE COMPANY CLASS file
**************************************************/

#include "Company.h"

/************* CONSTRUCTORS ******************/

Company::Company() {
    setCompanyName("None");
    setOwner("-------"); //initialize to be empty
}

Company::Company(string name) {
    companyName = name;
    owner = "-------"; //initialize to be empty
}

Company::Company(string newName, string newOwner, int newShares, int newSharePrice, int newCost){
    setCompanyName(newName);
    setOwner(newOwner);
    shares = newShares;
    sharePrice = newSharePrice;
    companyCost = newCost;
}

int Company::getCompanyCost() {
    return companyCost;
}

/************* ACCESSOR FUNCTIONS ******************/

int Company::getSharePrice() {
    return sharePrice;
}

void Company::setCompanyName(string name) {
    companyName = name;
}

string Company::getCompanyName() {
    return companyName;
}

string Company::getOwnerName() {
    return owner;
}

char Company::getKey() {
    char key = getCompanyName().at(1);
    return key;
}

int Company::getTotalShares() {
    return shares;
}

/************* MUTATOR FUNCTIONS ******************/


void Company::updateShares(int change) {
    int newshares = shares + change;
    if ( newshares >= 0) {
        shares = newshares;
    } else {
        shares = 0;
    }
}

void Company::setSharePrice(int level) {
    sharePrice = rand()%(level+4) + 1;
}

void Company::setOwner(string name) {
    owner = name;
}


void Company::setTotalShares(int playersNumber) {
    shares = companyCost + (rand()%11 + 10)*playersNumber;
}

void Company::setCompanyCost(int level) {
    companyCost = 2*5*level;
}






