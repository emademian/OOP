//
// Created by Ema Demian on 05.05.2022.
//

#include "UndoAdaugare.h"

void UndoAdaugare::doUndo() {
    repo.sterge_repo(locatar.get_ap());
}
