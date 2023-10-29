//
// Created by ADMIN on 16-Sep-23.
//

#include "Silver.h"

/**************************************************
 Project: Risky Business - Assigment 2 part B
 Author: Jash Nguyen (34327681)
 Purpose: Silver class application file
**************************************************/

Silver::Silver():Company() {
}

Silver::Silver(string name) : Company(name) {
    Company::setCompanyCost(level);
}

Silver::Silver(string newName, string newOwner, int newShares, int newSharePrice, int newCost) : Company(newName,
                                                                                                         newOwner,
                                                                                                         newShares,
                                                                                                         newSharePrice,
                                                                                                         newCost) {

}

int Silver::getLevel() {
    return level;
}

string Silver::getPower() {
    return power;
}

string Silver::getDetails() {
    stringstream companyDetails;
    companyDetails << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
    companyDetails << "\n Silver company: " << companyName;
    companyDetails << "\n Company's owner: " << owner;
    companyDetails << "\n Company level: " << level;
    companyDetails << "\n Company Power: " << power;
    companyDetails << "\n Company Cost: " << companyCost;
    companyDetails << "\n Total shares: " << getTotalShares();
    companyDetails << "\n Share price: " << getSharePrice();
    return companyDetails.str();
}





