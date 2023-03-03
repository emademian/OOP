//
// Created by Ema Demian on 24.04.2022.
//

#ifndef LAB8_9_OOP_LOCATAR_H
#define LAB8_9_OOP_LOCATAR_H


#include <string>
#include<iostream>
#include <vector>

using namespace std;


class Locatar {
private:
    int Ap;
    string Nume;
    int Sup;
    string Tip;
public:
    int get_ap() const;

    string get_nume() const;

    int get_sup() const;

    string get_tip() const;

    Locatar(int ap, const string &nume, int sup, const string &tip) {
        Ap = ap;
        Nume = nume;
        Sup = sup;
        Tip = tip;
    }

    Locatar() = default;

    ~Locatar() = default;

    Locatar(const Locatar &ot) {
        Ap = ot.Ap;
        Nume = ot.Nume;
        Sup = ot.Sup;
        Tip = ot.Tip;
    }

    void set_nume(string nume_nou);

    void set_sup(int sup_noua);

    void set_tip(string tip_nou);

};


#endif //LAB8_9_OOP_LOCATAR_H
