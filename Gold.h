//
// Created by ADMIN on 16-Sep-23.
//

#ifndef A2_JASHNGUYEN_GOLD_H
#define A2_JASHNGUYEN_GOLD_H
#include "Company.h"

class Gold: public Company{
private:
    int level = 5;
    string power = "assets";
public:
    Gold();
    Gold(string name);
    string getDetails();
    string getPower();
    int getLevel();

};


#endif //A2_JASHNGUYEN_GOLD_H
