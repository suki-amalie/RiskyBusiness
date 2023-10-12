//
// Created by ADMIN on 08-Sep-23.
//

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
    Company();
    Company(string name);
    virtual ~Company() = default;
    int getTotalShares();
    int getSharePrice();
    int getCompanyCost();
    virtual int getLevel() = 0;
    string getCompanyName();
    virtual string getPower() = 0;
    string getOwnerName();
    virtual string getDetails()  {return "print base class\n"; };
    char getKey();
    void setTotalShares(int playersNumber);
    void setCompanyCost(int level);
    void setSharePrice(int level);
    void setCompanyName(string name);
    void updateShares(int change);
    void setOwner(string name);
};


#endif //A2_JASHNGUYEN_COMPANY_H
