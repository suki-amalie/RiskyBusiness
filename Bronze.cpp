/**************************************************
 Project: Risky Business - Assigment 2 part B
 Author: Jash Nguyen (34327681)
 Purpose: BRONZE COMPANY CLASS file
**************************************************/

#include "Bronze.h"

Bronze::Bronze(): Company(){
}

Bronze::Bronze(string name) : Company(name) {
    Company::setCompanyCost(level);
}

Bronze::Bronze(string newName, string newOwner, int newShares, int newSharePrice, int newCost) : Company(newName,
                                                                                                         newOwner,
                                                                                                         newShares,
                                                                                                         newSharePrice,
                                                                                                         newCost) {

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







