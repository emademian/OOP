//
// Created by Ema Demian on 05.05.2022.
//

#ifndef LAB8_9_OOP_UNDOADAUGARE_H
#define LAB8_9_OOP_UNDOADAUGARE_H
#include "LocatarRepo.h"
#include "ActiuneUndo.h"
#include "Locatar.h"


class UndoAdaugare :public ActiuneUndo{
private:
    LocatarRepo& repo;
    Locatar locatar;
public:
    UndoAdaugare(LocatarRepo& repo,const Locatar& locatar):repo{repo},locatar{locatar},ActiuneUndo(){};
    void doUndo() override;
    virtual ~UndoAdaugare() {};
};


#endif //LAB8_9_OOP_UNDOADAUGARE_H
