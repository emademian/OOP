//
// Created by Ema Demian on 05.05.2022.
//

#ifndef LAB8_9_OOP_UNDOMODIFICARE_H
#define LAB8_9_OOP_UNDOMODIFICARE_H
#include "LocatarRepo.h"
#include "ActiuneUndo.h"
#include "Locatar.h"

class UndoModificare :public ActiuneUndo{
private:
    LocatarRepo& repo;
    Locatar locatar;
public:
    UndoModificare(LocatarRepo& repo,Locatar locatar):repo{repo},locatar{locatar},ActiuneUndo(){};
    void doUndo() override;
    virtual ~UndoModificare() {};
};


#endif //LAB8_9_OOP_UNDOMODIFICARE_H
