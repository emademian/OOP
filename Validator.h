//
// Created by Ema Demian on 24.04.2022.
//

#ifndef LAB8_9_OOP_VALIDATOR_H
#define LAB8_9_OOP_VALIDATOR_H


#include "Locatar.h"
#include <vector>

using namespace std;

class ValidareExceptii {
    vector<string> Mesaj;
public:
    ValidareExceptii(vector<string> &erori) {
        Mesaj = erori;
    }

    friend ostream &operator<<(ostream &out, const ValidareExceptii &exceptii);
};

ostream &operator<<(ostream &out, const ValidareExceptii &exceptii);

class Validator {
public:
    static int validare_locatar(Locatar &locatar);
};


#endif //LAB8_9_OOP_VALIDATOR_H
