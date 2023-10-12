//
// Created by ADMIN on 16-Sep-23.
//

#ifndef A2_JASHNGUYEN_SILVER_H
#define A2_JASHNGUYEN_SILVER_H
#include "Company.h"

class Silver: public Company{
private:
    int level = 4;
    string power = "shares";

public:
    Silver();
    Silver(string name);
    string getDetails();
    string getPower();
    int getLevel();

};


#endif //A2_JASHNGUYEN_SILVER_H
