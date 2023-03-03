//
// Created by Ema Demian on 24.04.2022.
//

#ifndef LAB8_9_OOP_LOCATARSERVICE_H
#define LAB8_9_OOP_LOCATARSERVICE_H


#include<string>
#include "LocatarRepo.h"
#include "Locatar.h"
#include "Validator.h"
#include <vector>
#include "../lab8_9_oop/ActiuneUndo.h"
#include "UndoAdaugare.h"
#include "UndoModificare.h"
#include "UndoStergere.h"

using namespace std;

class LocatarService {
private:
    LocatarRepo &Repo;
    Validator &Valid;
    vector<ActiuneUndo*> lista_undo;

public:
    LocatarService(LocatarRepo &repo, Validator &valid) noexcept: Repo{repo}, Valid{valid} {};

    vector<Locatar> &get_all_srv();

    void adauga_srv(int ap, const string &nume, int sup, const string &tip);

    void modifica_srv(int ap, const string &nume, int sup_noua, const string &tip_nou);

    void sterge_srv(int ap);

    Locatar cauta_srv(int ap);

    vector<Locatar> filtrare_tip(const string &tip);

    vector<Locatar> filtrare_sup(int sup);

    vector<Locatar> sortare(int opt);

    void undo();
};


#endif //LAB8_9_OOP_LOCATARSERVICE_H
