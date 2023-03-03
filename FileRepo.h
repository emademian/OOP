//
// Created by Ema Demian on 05.05.2022.
//

#ifndef LAB8_9_OOP_FILEREPO_H
#define LAB8_9_OOP_FILEREPO_H
#include "LocatarRepo.h"
#include <fstream>
using namespace std;


class FileRepo :public LocatarRepo{
private:
    string fisier="";
    void incarca_repo();
    void scrie_repo();
public:
    FileRepo(string fisier):LocatarRepo(),fisier{fisier}
    {
        incarca_repo();
    }
    void adauga_repo(const Locatar &locatar) override {
        LocatarRepo::adauga_repo(locatar);
        scrie_repo();
    }
    void sterge_repo(int ap) override {
        LocatarRepo::sterge_repo(ap);
        scrie_repo();
    }
};


#endif //LAB8_9_OOP_FILEREPO_H
