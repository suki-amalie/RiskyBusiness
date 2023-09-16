//
// Created by ADMIN on 08-Sep-23.
//

#include "Company.h"
Company::Company() {
    owner = "-------"; //initialize to be empty
}


int Company::getCompanyWorth() {
    return companyWorth;
}

string Company::getPower() {
    return power;
}

int Company::getSharePrice() {
    return sharePrice;
}

string Company::getDetails() {
    stringstream companyDetails;
    companyDetails << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
    companyDetails << "\n Company Name: " << companyName;
    companyDetails << "\n Company level: " << level;
    companyDetails << "\n Company Power: " << power;
    companyDetails << "\n Company Worth: " << companyWorth;
    return companyDetails.str();
}


Company::Company(string name, int newLevel, string power) {
    setCompanyName(name);
    level = newLevel;
    power = power;
    setCompanyCost();
    setOwner("-------");
    setSharePrice();
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
    char key = companyName.at(1);
    return key;
}

void Company::updateShares(int change) {
    shares += change;
}

void Company::setSharePrice(int value) {
    sharePrice = value;
}

int Company::getCompanyLevel() {
    return level;
}

int Company::getTotalShares() {
    return shares;
}

void Company::setOwner(string name) {
    owner = name;
}

void Company::setCompanyCost() {
    companyWorth = 2*5*level;
}

Company::Company(string name) {
    setCompanyName(name);
    setOwner("-------");
    setSharePrice(); //randomise the share price based on the company level to fit within the range of 1-(level+4
    setCompanyCost(); //2*5*company level
}

void Company::setTotalShares(int amount) {
    shares = amount;
}


