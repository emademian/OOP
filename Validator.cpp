//
// Created by Ema Demian on 06.04.2022.
//

#include "Validator.h"
#include "Locatar.h"
#include<vector>

using namespace std;

int Validator::validare_locatar(Locatar &locatar) {
    vector<string> mesaj;
    if (locatar.get_ap() <= 0)
        mesaj.emplace_back("Apartament invalid.\n");
    if (locatar.get_nume().empty())
        mesaj.emplace_back("Nume invalid.\n");
    if (locatar.get_sup() <= 0)
        mesaj.emplace_back("Suprafata invalida.\n");
    if (locatar.get_tip().empty())
        mesaj.emplace_back("Tip invalid.\n");
    if (mesaj.size() > 0)
        throw ValidareExceptii(mesaj);
    return 0;
}

ostream &operator<<(ostream &out, const ValidareExceptii &exceptii) {
    for (const auto &mesaj: exceptii.Mesaj) {
        if (&mesaj != nullptr)
            out << mesaj << " ";
    }
    return out;
}