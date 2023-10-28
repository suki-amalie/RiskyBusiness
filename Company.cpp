//
// Created by ADMIN on 08-Sep-23.
//

#include "Company.h"
Company::Company() {
    owner = "-------"; //initialize to be empty
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

void Company::updateShares(int change) {
    shares += change;
}

void Company::setSharePrice(int level) {
    sharePrice = rand()%4 + 1;
}


int Company::getTotalShares() {
    return shares;
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

int Company::getCompanyCost() {
    return companyCost;
}




