//
// Created by Ema Demian on 31.03.2022.
//
#include<iostream>
#include "LocatarService.h"
#include "Locatar.h"
#include "Validator.h"
#include <utility>
#include <vector>
#include <algorithm>


vector<Locatar> &LocatarService::get_all_srv() {
    return Repo.get_all_repo();
}

void LocatarService::adauga_srv(int ap, const string &nume, int sup, const string &tip) {
    Locatar locatar(ap, nume, sup, tip);
    Validator::validare_locatar(locatar);
    Repo.adauga_repo(locatar);
    ActiuneUndo *op_undo = new UndoAdaugare{Repo, locatar};
    lista_undo.push_back(op_undo);
}

void LocatarService::modifica_srv(int ap, const string &nume_nou, int sup_noua, const string &tip_nou) {
    Locatar locatar(ap, nume_nou, sup_noua, tip_nou);
    Validator::validare_locatar(locatar);
    Locatar locatar1=Repo.cauta_repo(ap);
    Repo.modifica_repo(locatar);
    ActiuneUndo *op_undo = new UndoModificare{Repo, locatar1};
    lista_undo.push_back(op_undo);
}

void LocatarService::sterge_srv(int ap) {
    Locatar locatar = Repo.cauta_repo(ap);
    Repo.sterge_repo(ap);
    ActiuneUndo *op_undo = new UndoStergere{Repo, locatar};
    lista_undo.push_back(op_undo);
}

Locatar LocatarService::cauta_srv(int ap) {
    return Repo.cauta_repo(ap);
}


vector<Locatar> LocatarService::filtrare_tip(const string &tip) {
    vector<Locatar> locatari = Repo.get_all_repo();
    vector<Locatar> lista_filtrata;
    /*
    for (auto &i: locatari)
        if (i.get_tip() == tip)
            lista_filtrata.push_back(i);
    return lista_filtrata;*/
    copy_if(locatari.begin(), locatari.end(), back_inserter(lista_filtrata),
            [tip](const Locatar &l) { return l.get_tip() == tip; });
    return lista_filtrata;
}

vector<Locatar> LocatarService::filtrare_sup(int sup) {
    vector<Locatar> locatari = Repo.get_all_repo();
    vector<Locatar> lista_filtrata;/*
    for (auto &i: locatari)
        if (i.get_sup() == sup)
            lista_filtrata.push_back(i);
    return lista_filtrata;*/
    copy_if(locatari.begin(), locatari.end(), back_inserter(lista_filtrata),
            [sup](const Locatar &l) { return l.get_sup() == sup; });
    return lista_filtrata;
}


vector<Locatar> LocatarService::sortare(int opt) {
    vector<Locatar> locatari = Repo.get_all_repo();
    if (opt == 1) {
        sort(locatari.begin(), locatari.end(), [](Locatar a, Locatar b) { return a.get_nume() < b.get_nume(); });
        return locatari;
    }
    if (opt == 2) {
        sort(locatari.begin(), locatari.end(), [](Locatar a, Locatar b) { return a.get_sup() < b.get_sup(); });
        return locatari;
    }
    return {};
}

void LocatarService::undo() {
    if (lista_undo.empty())
        return;
    lista_undo[lista_undo.size() - 1]->doUndo();
    lista_undo.pop_back();
}