//
// Created by Ema Demian on 31.03.2022.
//
#include<iostream>
#include <utility>
#include "Console.h"
#include "LocatarService.h"
#include "LocatarRepo.h"
#include <vector>
#include <fstream>

using namespace std;


void Console::meniu() {
    cout << "1.Adauga locatar" << endl;
    cout << "2.Afiseaza locatari" << endl;
    cout << "3.Modifica locatar" << endl;
    cout << "4.Sterge locatar" << endl;
    cout << "5.Cauta apartament" << endl;
    cout << "6.Filtrare" << endl;
    cout << "7.Sortare" << endl;
    cout << "8.Adauga apartament" << endl;
    cout << "9.Goleste lista" << endl;
    cout << "10.Genereaza lista" << endl;
    cout << "11.Salveaza HTML" << endl;
    cout << "12.Undo" << endl;
    cout << "0.Exit" << endl;
}

void Console::adauga_ui() {
    int ap;
    string nume;
    int sup;
    string tip;
    cout << "Introduceti numarul apartamentului: ";
    cin >> ap;
    cout << "Introduceti numele locatarului: ";
    cin >> nume;
    cout << "Introduceti suprafata apartamentului: ";
    cin >> sup;
    cout << "Introduceti tipul apartamentului: ";
    cin >> tip;
    try {
        Service.adauga_srv(ap, nume, sup, tip);
        cout << "Locatar adaugat cu succes" << endl;
    } catch (RepoExceptii &ex) {
        cout << ex<<endl;
    }
    catch (ValidareExceptii &ex) {
        cout << ex << endl;
    }
}

void Console::afisare_ui() {
    vector<Locatar> &locatari = Service.get_all_srv();
    for (const auto &i: locatari)
        cout << "Ap: " << i.get_ap() << " || Nume: " << i.get_nume() << " || Sup: "
             << i.get_sup() << " || Tip: " << i.get_tip() << endl;
}

void Console::modifica_ui() {
    int ap, sup_noua;
    string nume_nou, tip_nou;
    cout << "Introduceti numarul apartamentului de modificat: ";
    cin >> ap;
    cout << "Introduceti numele nou: ";
    cin >> nume_nou;
    cout << "Introduceti suprafata noua: ";
    cin >> sup_noua;
    cout << "Introduceti tipul nou: ";
    cin >> tip_nou;
    try {
        Service.modifica_srv(ap, nume_nou, sup_noua, tip_nou);
        cout << "Locatar modificat cu succes" << endl;
    } catch (RepoExceptii &ex) {
        cout << ex<<endl;
    }
    catch (ValidareExceptii &ex) {
        cout << ex << endl;
    }
}

void Console::sterge_ui() {
    int ap;
    cout << "Introduceti nr apartamentului de sters: ";
    cin >> ap;
    try {
        Service.sterge_srv(ap);
        cout << "Apartament sters cu succes" << endl;
    } catch (RepoExceptii &ex) {
        cout << ex<<endl;
    }
}

void Console::cauta_ui() {
    int ap;
    cout << "Introduceti nr apartamentului cautat: ";
    cin >> ap;
    try {
        Locatar locatar = Service.cauta_srv(ap);
        cout << "Ap: " << locatar.get_ap() << " || Nume: " << locatar.get_nume() << " || Sup: "
             << locatar.get_sup() << " || Tip: " << locatar.get_tip() << endl;
    } catch (RepoExceptii &ex) {
        cout << ex<<endl;
    }
}

void Console::filtrare_ui() {
    int opt, sup;
    string tip;
    cout << "Filtrati dupa:\n1.Tip\n2.Suprafata\nIntroduceti optiunea:";
    cin >> opt;
    if (opt == 1) {
        cout << "Introduceti tipul:";
        cin >> tip;
        vector<Locatar> lista_filtrata = Service.filtrare_tip(tip);
        if (lista_filtrata.empty())
            cout << "Tip inexistent"<<endl;
        else
            for (const auto &i: lista_filtrata)
                cout << "Ap: " << i.get_ap() << " || Nume: " << i.get_nume()
                     << " || Sup: "
                     << i.get_sup() << " || Tip: " << i.get_tip() << endl;
    }
    if (opt == 2) {
        cout << "Introduceti suprafata:";
        cin >> sup;
        vector<Locatar> lista_filtrata = Service.filtrare_sup(sup);
        if (lista_filtrata.empty())
            cout << "Suprafata inexistenta"<<endl;
        else
            for (const auto &i: lista_filtrata)
                cout << "Ap: " << i.get_ap() << " || Nume: " << i.get_nume()
                     << " || Sup: "
                     << i.get_sup() << " || Tip: " << i.get_tip() << endl;
    }
    if (opt != 1 && opt != 2)
        cout << "Optiune inexistenta"<<endl;
}

void Console::sortare_ui() {
    int opt;
    cout << "Sortati dupa:\n1.Nume\n2.Suprafata\nIntroduceti optiunea:";
    cin >> opt;
    if (opt == 1 || opt == 2) {
        vector<Locatar> lista_sortata = Service.sortare(opt);
        for (const auto &i: lista_sortata)
            cout << "Ap: " << i.get_ap() << " || Nume: " << i.get_nume()
                 << " || Sup: "
                 << i.get_sup() << " || Tip: " << i.get_tip() << endl;
    } else
        cout << "Optiune inexistenta"<<endl;
}

void Console::adauga_not_ui() {
    int ap;
    cout << "Introduceti nr apartamentului:";
    cin >> ap;
    Notificare.adauga(ap);
    cout << "Sunt " << Notificare.dim() << " apartamente in lista" << endl;
    for (const auto &i: Notificare.notificari())
        cout << "Ap: " << i.get_ap() << " || Nume: " << i.get_nume() << " || Sup: "
             << i.get_sup() << " || Tip: " << i.get_tip() << endl;
}

void Console::goleste_not_ui() {
    Notificare.goleste();
    cout << "Lista de notificari e goala" << endl;
}

void Console::gen_random_not_ui() {
    int nr;
    cout << "Introduceti nr de apartamente de generat:";
    cin >> nr;
    if (nr <= Service.get_all_srv().size()) {
        Notificare.genereaza_random(nr);
        cout << "Sunt " << Notificare.dim() << " apartamente in lista" << endl;
        for (const auto &i: Notificare.notificari())
            cout << "Ap: " << i.get_ap() << " || Nume: " << i.get_nume() << " || Sup: "
                 << i.get_sup() << " || Tip: " << i.get_tip() << endl;
    } else
        cout << "Nu exista destule apartamente"<<endl;
}

void Console::salveaza_HTML() {
    string fisier;
    cout << "Dati numele fisierului: ";
    cin >> fisier;
    fisier.append(".html");
    ofstream fout(fisier);
    fout << "====LISTA====" << " <p> ";
    fout << "<html><body>" << '\n';
    fout << "<table border=\"1\" style=\"width:100 % \">" << '\n';
    for (auto &locatar: Notificare.notificari()) {
        fout << "<tr>";
        fout << "<td>" << locatar.get_ap() << "</td>" << '\n';
        fout << "<td>" << locatar.get_nume() << "</td>" << '\n';
        fout << "<td>" << locatar.get_tip() << "</td>" << '\n';
        fout << "<td>" << locatar.get_sup() << "</td>" << '\n';
        fout << "</tr>" << '\n';
    }
    fout << "</table>" << '\n';
    fout << "</body></html>" << '\n';
    cout << "Salvare realizata cu succes!\n\n";
    fout.close();
}

void Console::run_console() {
    int ok = 1;
    int cmd;
    while (ok) {
        meniu();
        cout << "Introduceti comanda:";
        cin >> cmd;
        if (cmd == 0)
            ok = 0;
        if (cmd == 1)
            adauga_ui();
        if (cmd == 2)
            afisare_ui();
        if (cmd == 3)
            modifica_ui();
        if (cmd == 4)
            sterge_ui();
        if (cmd == 5)
            cauta_ui();
        if (cmd == 6)
            filtrare_ui();
        if (cmd == 7)
            sortare_ui();
        if (cmd == 8)
            adauga_not_ui();
        if (cmd == 9)
            goleste_not_ui();
        if (cmd == 10)
            gen_random_not_ui();
        if (cmd == 11)
            salveaza_HTML();
        if (cmd == 12) {
            try {
                Service.undo();
            } catch (RepoExceptii &ex) {
                cout << ex<<endl;
            }
        }
    }
}

