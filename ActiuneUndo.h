//
// Created by Ema Demian on 05.05.2022.
//

#ifndef LAB8_9_OOP_ACTIUNEUNDO_H
#define LAB8_9_OOP_ACTIUNEUNDO_H


class ActiuneUndo {
public:
    virtual void doUndo()=0;
    ActiuneUndo() {};
    virtual ~ActiuneUndo(){};
};


#endif //LAB8_9_OOP_ACTIUNEUNDO_H
