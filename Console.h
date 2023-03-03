//
// Created by Ema Demian on 24.04.2022.
//

#ifndef LAB8_9_OOP_CONSOLE_H
#define LAB8_9_OOP_CONSOLE_H


#include "LocatarService.h"
#include <vector>
#include "Notificare.h"



class Console {
    LocatarService &Service;
    Notificare &Notificare;
public:
    Console(LocatarService &service, class Notificare &notificare) noexcept: Service{service},
                                                                             Notificare{notificare} {};

    void run_console();

    static void meniu();

    void adauga_ui();

    void afisare_ui();

    void modifica_ui();

    void sterge_ui();

    void cauta_ui();

    void filtrare_ui();

    void sortare_ui();

    void adauga_not_ui();

    void goleste_not_ui();

    void gen_random_not_ui();

    void salveaza_HTML();
};


#endif //LAB8_9_OOP_CONSOLE_H
