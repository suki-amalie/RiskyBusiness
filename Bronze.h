//
// Created by ADMIN on 16-Sep-23.
//

#ifndef A2_JASHNGUYEN_BRONZE_H
#define A2_JASHNGUYEN_BRONZE_H
#include "Company.h"
#include "Player.h"
using namespace std;

class Bronze: public Company{
private:
    int level = 3;
public:
    Bronze(string name);
    void usePower(Player &player);


};


#endif //A2_JASHNGUYEN_BRONZE_H
