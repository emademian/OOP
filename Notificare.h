//
// Created by Ema Demian on 04.05.2022.
//

#ifndef LAB8_9_NOTIFICARE_H
#define LAB8_9_NOTIFICARE_H

#include "LocatarRepo.h"
#include <vector>
#include "Locatar.h"
#include "Observer.h"

class Notificare :public Observable{
private:
    LocatarRepo &repo;
    vector<Locatar> locatari;
public:
    Notificare() = default;

    Notificare(LocatarRepo &repo) : repo{repo} {}

    size_t dim();

    void adauga(int ap);

    void goleste();

    void genereaza_random(int nr);

    vector<Locatar> notificari() const;
};


#endif //LAB8_9_NOTIFICARE_H
