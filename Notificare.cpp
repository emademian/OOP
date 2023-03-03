//
// Created by Ema Demian on 04.05.2022.
//

#include "Notificare.h"
#include <random>
#include <algorithm>

size_t Notificare::dim() {
    return locatari.size();
}

void Notificare::adauga(int ap) {
    vector<Locatar> locatari1{repo.get_all_repo()};
    for (const auto &l: locatari1) {
        if (l.get_ap() == ap) {
            locatari.push_back(l);
            notify();
        }
    }

}

void Notificare::goleste() {
    locatari.clear();
    notify();
}

Locatar random(vector<Locatar> &vector) {
    int nr_random = rand() % vector.size();
    return vector[nr_random];
}

void Notificare::genereaza_random(int nr) {
    vector<Locatar> locatari1{repo.get_all_repo()};
    while (nr) {
        locatari.push_back(random(locatari1));
        nr--;
    }
    notify();
}

vector<Locatar> Notificare::notificari() const{
    return locatari;
}