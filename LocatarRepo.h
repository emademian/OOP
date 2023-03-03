//
// Created by Ema Demian on 24.04.2022.
//

#ifndef LAB8_9_OOP_LOCATARREPO_H
#define LAB8_9_OOP_LOCATARREPO_H


#include "Locatar.h"
#include <utility>
#include <vector>

using namespace std;

class RepoExceptii {
    string Mesaj;
public:
    RepoExceptii(string mesaj) {
        Mesaj = mesaj;
    }

    friend ostream &operator<<(ostream &out, const RepoExceptii &ex);
};

ostream &operator<<(ostream &out, const RepoExceptii &ex);

class LocatarRepo {
private:
    vector<Locatar> locatari;
public:
    vector<Locatar> &get_all_repo();

    virtual void adauga_repo(const Locatar &locatar);

    void modifica_repo(const Locatar &locatar);

    virtual void sterge_repo(int ap);

    Locatar cauta_repo(int ap);

    bool exista(int ap);

    LocatarRepo() = default;
    virtual ~LocatarRepo()=default;

    LocatarRepo(const LocatarRepo &ot) = delete;
};


#endif //LAB8_9_OOP_LOCATARREPO_H
