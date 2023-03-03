//
// Created by Ema Demian on 31.03.2022.
//

#include "LocatarRepo.h"
#include "Locatar.h"


using namespace std;

vector<Locatar> &LocatarRepo::get_all_repo() {
    return locatari;
}

void LocatarRepo::adauga_repo(const Locatar &locatar) {
    for (const Locatar &loc: locatari) {
        if (loc.get_ap() == locatar.get_ap()) {
            throw RepoExceptii("Locatar existent\n");
        }
    }
    locatari.push_back(locatar);
}

void LocatarRepo::modifica_repo(const Locatar &locatar) {
    if (!exista(locatar.get_ap())) {
        throw RepoExceptii("Locatar inexistent\n");
    }
    for (auto &i: locatari) {
        if (locatar.get_ap() == i.get_ap()) {
            i.set_nume(locatar.get_nume());
            i.set_sup(locatar.get_sup());
            i.set_tip(locatar.get_tip());
        }
    }
}

void LocatarRepo::sterge_repo(int ap) {
    if (!exista(ap)) {
        throw RepoExceptii("Apartament inexistent\n");
    }
    for (int i = 0; i < locatari.size(); i++) {
        if (locatari[i].get_ap() == ap) {
            locatari.erase(locatari.begin() + i);
            return;
        }
    }
}

Locatar LocatarRepo::cauta_repo(int ap) {/*
    for (auto &i: locatari) {
        if (i.get_ap() == ap)
            return i;
    }*/
    vector<Locatar> locatari = get_all_repo();
    auto i = find_if(locatari.begin(), locatari.end(),
                         [ap](const Locatar &l) { return l.get_ap() == ap; });
    if(i!=locatari.end())
        return *i;
    throw RepoExceptii("Apartament inexistent\n");
}

bool LocatarRepo::exista(int ap) {
    try {
        cauta_repo(ap);
        return true;
    }
    catch (RepoExceptii &) {
        return false;
    }
}

ostream& operator<<(ostream& out,const RepoExceptii& ex){
    out<<ex.Mesaj;
    return out;
}

