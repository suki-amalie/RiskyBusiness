/**************************************************
 Project: Risky Business - Assigment 2 part B
 Author: Jash Nguyen (34327681)
 Purpose: GOLD COMPANY CLASS file
**************************************************/

#include "Gold.h"

Gold::Gold():Company() {
}

Gold::Gold(string name) : Company(name) {
    Company::setCompanyCost(level);
}

Gold::Gold(string newName, string newOwner, int newShares, int newSharePrice, int newCost) : Company(newName, newOwner,
                                                                                                     newShares,
                                                                                                     newSharePrice,
                                                                                                     newCost) {

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






