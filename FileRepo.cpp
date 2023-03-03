//
// Created by Ema Demian on 05.05.2022.
//

#include "FileRepo.h"
#include <fstream>
#include "Locatar.h"
#include<sstream>


void FileRepo::incarca_repo() {
    ifstream in(fisier);
    if(!in.is_open())
        throw RepoExceptii("Fisierul nu poate fi deschis");
    while(!in.eof()){
        int ap;
        in>>ap;
        string nume;
        in>>nume;
        int sup;
        in>>sup;
        string tip;
        in>>tip;
        if(in.eof())
            break;
        Locatar locatar{ap,nume,sup,tip};
        LocatarRepo::adauga_repo(locatar);
    }/*
    string line;
    while (getline(in, line)) {
        string nume,tip;
        int ap,sup;
        stringstream linestream(line);
        string current_item;
        int item_no = 0;
        while (getline(linestream, current_item, ',')) {
            if (item_no == 0) ap = stoi(current_item);
            if (item_no == 1) nume = current_item;
            if (item_no == 2) tip = current_item;
            if (item_no == 3) sup = stoi(current_item);
            item_no++;
        }
        Locatar locatar{ap,nume,tip,sup};
        LocatarRepo::adaug;
    }*/
    in.close();
}

void FileRepo::scrie_repo() {
    ofstream out(fisier);
    if(!out.is_open())
        throw RepoExceptii("Fisierul nu poate fi deschis");
    for(auto& locatar:get_all_repo()){
        out<<locatar.get_ap();
        out<<endl;
        out<<locatar.get_nume();
        out<<endl;
        out<<locatar.get_sup();
        out<<endl;
        out<<locatar.get_tip();
        out<<endl;
    }
    out.close();
}

