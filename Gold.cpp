//
// Created by ADMIN on 16-Sep-23.
//

#include "Gold.h"

Gold::Gold():Company() {
}

Gold::Gold(string name) : Company(name) {
    Company::setCompanyCost(level);
}

string Gold::getDetails() {
    stringstream companyDetails;
    companyDetails << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
    companyDetails << "\n Gold Name: " << companyName;
    companyDetails << "\n Company's owner: " << getOwnerName();
    companyDetails << "\n Company level: " << level;
    companyDetails << "\n Company Power: " << power;
    companyDetails << "\n Company Worth: " << companyCost;
    companyDetails << "\n Total shares: " << getTotalShares();
    companyDetails << "\n Share price: " << getSharePrice();
    return companyDetails.str();
}

int Gold::getLevel() {
    return level;
}

string Gold::getPower() {
    return power;
}


