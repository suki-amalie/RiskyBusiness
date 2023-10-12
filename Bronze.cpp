//
// Created by ADMIN on 16-Sep-23.
//

#include "Bronze.h"

Bronze::Bronze(): Company(){
}

Bronze::Bronze(string name) : Company(name) {
    Company::setCompanyCost(level);
}

string Bronze::getDetails() {
    stringstream companyDetails;
    companyDetails << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
    companyDetails << "\n Bronze company: " << getCompanyName();
    companyDetails << "\n Company's owner: " << getOwnerName();
    companyDetails << "\n Company level: " << getLevel();
    companyDetails << "\n Company Power: " << getPower();
    companyDetails << "\n Company Cost: " << getCompanyCost();
    companyDetails << "\n Total shares: " << getTotalShares();
    companyDetails << "\n Share price: " << getSharePrice();
    return companyDetails.str();
}


int Bronze::getLevel() {
    return level;
}

string Bronze::getPower() {
    return power;
}



