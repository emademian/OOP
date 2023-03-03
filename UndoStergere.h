//
// Created by Ema Demian on 05.05.2022.
//

#ifndef LAB8_9_OOP_UNDOSTERGERE_H
#define LAB8_9_OOP_UNDOSTERGERE_H
#include "LocatarRepo.h"
#include "ActiuneUndo.h"
#include "Locatar.h"

class UndoStergere :public ActiuneUndo{
private:
    LocatarRepo& repo;
    Locatar locatar;
public:
    UndoStergere(LocatarRepo& repo,Locatar locatar):repo{repo},locatar{locatar},ActiuneUndo(){};
    void doUndo() override;
    virtual ~UndoStergere() {};
};


#endif //LAB8_9_OOP_UNDOSTERGERE_H
