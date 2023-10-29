/**************************************************
 Project: Risky Business - Assigment 2 part B
 Author: Jash Nguyen
 Purpose: BASE COMPANY CLASS Header file
**************************************************/

#ifndef A2_JASHNGUYEN_COMPANY_H
#define A2_JASHNGUYEN_COMPANY_H


#include <string>
#include <sstream>
#include <iostream>

using namespace std;

class Company {
protected:
    string companyName;
    int shares;
    int sharePrice;
    int companyCost;
    string owner = "-------"; //initialize to be empty
public:
    // constructors
    Company();
    Company(string name);
    Company(string newName, string newOwner, int newShares, int newSharePrice, int newCost);
    virtual ~Company() = default;

    // accessor functions
    int getTotalShares();
    int getSharePrice();
    int getCompanyCost();
    virtual int getLevel() = 0;
    string getCompanyName();
    virtual string getPower() = 0;
    string getOwnerName();
    virtual string getDetails()  {return "print base class\n"; };
    char getKey();

    // mutators
    void setTotalShares(int playersNumber);
    void setCompanyCost(int level);
    void setSharePrice(int level);
    void setCompanyName(string name);
    void updateShares(int change);
    void setOwner(string name);
};


#endif //A2_JASHNGUYEN_COMPANY_H
