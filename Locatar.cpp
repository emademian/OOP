//
// Created by Ema Demian on 31.03.2022.
//

#include "Locatar.h"

#include <utility>

using namespace std;

int Locatar::get_ap() const {
    return Ap;
}

string Locatar::get_nume() const {
    return Nume;
}

int Locatar::get_sup() const {
    return Sup;
}

string Locatar::get_tip() const {
    return Tip;
}

void Locatar::set_nume(string nume_nou) {
    Nume = std::move(nume_nou);
}

void Locatar::set_sup(int sup_noua) {
    Sup = sup_noua;
}

void Locatar::set_tip(string tip_nou) {
    Tip = std::move(tip_nou);
}