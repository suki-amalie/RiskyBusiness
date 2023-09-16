//
// Created by ADMIN on 08-Sep-23.
//

#ifndef A2_JASHNGUYEN_COMPANY_H
#define A2_JASHNGUYEN_COMPANY_H


#include <string>
#include <sstream>
using namespace std;

class Company {
protected:
    string companyName;
    int shares;
    int sharePrice;
    int companyWorth; //Initialize to be 2 x (5 x level)
    string owner; //initialize to be empty
    string power;
    int level; //(1=Bronze, 2=Silver, 3=Gold)
public:
    Company();
    Company(string name);
    ~Company();
    Company(string name, int newLevel, string power);
    int getTotalShares();
    int getSharePrice();
    int getCompanyWorth();
    int getCompanyLevel();
    string getCompanyName();
    string getPower();
    string getOwnerName();
    string getDetails();
    char getKey();
    void setTotalShares(int amount);
    void setSharePrice(int value);
    void setCompanyCost();
    void setCompanyName(string name);
    void updateShares(int change);
    void setOwner(string name);
};


#endif //A2_JASHNGUYEN_COMPANY_H
