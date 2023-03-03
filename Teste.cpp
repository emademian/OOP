//
// Created by Ema Demian on 06.04.2022.
//

#include "Teste.h"
#include <assert.h>
#include "Locatar.h"
#include "LocatarRepo.h"
#include "LocatarService.h"
#include "Validator.h"
#include <vector>
#include "Notificare.h"
#include <fstream>
#include "FileRepo.h"


void test_creeaza() {
    Locatar locatar = Locatar(1, "Ema", 50, "decomandat");
    assert(locatar.get_ap() == 1);
    assert(locatar.get_nume() == "Ema");
    assert(locatar.get_sup() == 50);
    assert(locatar.get_tip() == "decomandat");
    locatar.set_nume("Maria");
    assert(locatar.get_nume() == "Maria");
    locatar.set_sup(100);
    assert(locatar.get_sup() == 100);
    locatar.set_tip("garsoniera");
    assert(locatar.get_tip() == "garsoniera");
}

void test_validare() {
    Locatar locatar = Locatar(-1, "Ema", 50, "decomandat");
    try {
        Validator::validare_locatar(locatar);
        assert(false);
    } catch (ValidareExceptii &ex) {
        assert(true);
    }
    Locatar locatar1 = Locatar(1, "", 50, "decomandat");
    try {
        Validator::validare_locatar(locatar1);
        assert(false);
    } catch (ValidareExceptii &ex) {
        assert(true);
    }
    Locatar locatar2 = Locatar(1, "Ema", -50, "decomandat");
    try {
        Validator::validare_locatar(locatar2);
        assert(false);
    } catch (ValidareExceptii &ex) {
        assert(true);
    }
    Locatar locatar3 = Locatar(1, "Ema", 50, "");
    try {
        Validator::validare_locatar(locatar3);
        assert(false);
    } catch (ValidareExceptii &ex) {
        assert(true);
    }
}

void test_adauga_srv() {
    LocatarRepo repo;
    Validator valid;
    LocatarService service = LocatarService(repo, valid);
    vector<Locatar> locatari = service.get_all_srv();
    assert(locatari.size() == 0);
    service.adauga_srv(1, "Ema", 50, "decomandat");
    vector<Locatar> locatari1 = service.get_all_srv();
    assert(locatari1.size() == 1);
    try {
        service.adauga_srv(1, "Ema", 50, "decomandat");
        assert(false);
    }
    catch (RepoExceptii &ex) {
        assert(true);
    }
}

void test_adauga_repo() {
    LocatarRepo repo;
    Locatar locatar(10, "Dan", 200, "decomandat");
    repo.adauga_repo(locatar);
    vector<Locatar> locatari = repo.get_all_repo();
    assert(locatari.size() == 1);
    try {
        repo.adauga_repo(locatar);
        assert(false);
    }
    catch (RepoExceptii &ex) {
        assert(true);
    }
}

void test_modifica_srv() {
    LocatarRepo repo;
    Validator valid;
    LocatarService service = LocatarService(repo, valid);
    service.adauga_srv(1, "Ema", 50, "decomandat");
    service.modifica_srv(1, "Maria", 100, "garsoniera");
    vector<Locatar> locatari = service.get_all_srv();
    assert(locatari[0].get_nume() == "Maria");
    assert(locatari[0].get_sup() == 100);
    assert(locatari[0].get_tip() == "garsoniera");
}

void test_modifica_repo() {
    LocatarRepo repo;
    Locatar locatar(10, "Dan", 200, "decomandat");
    Locatar locatar1(10, "Maria", 100, "garsoniera");
    repo.adauga_repo(locatar);
    repo.modifica_repo(locatar1);
    vector<Locatar> locatari = repo.get_all_repo();
    assert(locatari[0].get_nume() == "Maria");
    assert(locatari[0].get_sup() == 100);
    assert(locatari[0].get_tip() == "garsoniera");
    Locatar locatar3(9, "Maria", 100, "garsoniera");
    try {
        repo.modifica_repo(locatar3);
        assert(false);
    }
    catch (RepoExceptii &ex) {
        assert(true);
    }
}

void test_sterge_srv() {
    LocatarRepo repo;
    Validator valid;
    LocatarService service = LocatarService(repo, valid);
    vector<Locatar> locatari = service.get_all_srv();
    assert(locatari.size() == 0);
    service.adauga_srv(1, "Ema", 50, "decomandat");
    vector<Locatar> locatari1 = service.get_all_srv();
    assert(locatari1.size() == 1);
    service.sterge_srv(1);
    vector<Locatar> locatari2 = service.get_all_srv();
    assert(locatari2.size() == 0);
}

void test_sterge_repo() {
    LocatarRepo repo;
    Locatar locatar(10, "Dan", 200, "decomandat");
    repo.adauga_repo(locatar);
    vector<Locatar> locatari = repo.get_all_repo();
    assert(locatari.size() == 1);
    try {
        repo.sterge_repo(9);
        assert(false);
    }
    catch (RepoExceptii &ex) {
        assert(true);
    }
    repo.sterge_repo(10);
    vector<Locatar> locatari1 = repo.get_all_repo();
    assert(locatari1.empty());
}

void test_cauta_srv() {
    LocatarRepo repo;
    Validator valid;
    LocatarService service = LocatarService(repo, valid);
    service.adauga_srv(1, "Ema", 50, "decomandat");
    Locatar locatar = service.cauta_srv(1);
    assert(locatar.get_nume() == "Ema");
}

void test_cauta_repo() {
    LocatarRepo repo;
    Locatar locatar(10, "Dan", 200, "decomandat");
    repo.adauga_repo(locatar);
    Locatar locatar1 = repo.cauta_repo(10);
    assert(locatar1.get_nume() == "Dan");
    try {
        repo.cauta_repo(9);
        assert(false);
    }
    catch (RepoExceptii &ex) {
        assert(true);
    }
}

void test_filtrare_tip() {
    LocatarRepo repo;
    Validator valid;
    LocatarService service = LocatarService(repo, valid);
    service.adauga_srv(1, "Ema", 50, "decomandat");
    service.adauga_srv(2, "Ema", 100, "decomandat");
    service.adauga_srv(3, "Ema", 50, "garsoniera");
    vector<Locatar> lista_filtrata = service.filtrare_tip("decomandat");
    assert(lista_filtrata.size() == 2);
}

void test_filtrare_sup() {
    LocatarRepo repo;
    Validator valid;
    LocatarService service = LocatarService(repo, valid);
    service.adauga_srv(1, "Ema", 50, "decomandat");
    service.adauga_srv(2, "Ema", 100, "decomandat");
    service.adauga_srv(3, "Ema", 50, "garsoniera");
    vector<Locatar> lista_filtrata = service.filtrare_sup(50);
    assert(lista_filtrata.size() == 2);
}

void test_sortare_nume() {
    LocatarRepo repo;
    Validator valid;
    LocatarService service = LocatarService(repo, valid);
    service.adauga_srv(1, "Ema", 50, "decomandat");
    service.adauga_srv(2, "Ana", 100, "comandat");
    service.adauga_srv(3, "Zara", 50, "garsoniera");
    vector<Locatar> locatari = service.sortare(1);
    assert(locatari[0].get_nume() == "Ana");
    assert(locatari[1].get_nume() == "Ema");
    assert(locatari[2].get_nume() == "Zara");
}

void test_sortare_sup() {
    LocatarRepo repo;
    Validator valid;
    LocatarService service = LocatarService(repo, valid);
    service.adauga_srv(1, "Ema", 50, "decomandat");
    service.adauga_srv(2, "Ana", 70, "comandat");
    service.adauga_srv(3, "Zara", 60, "garsoniera");
    vector<Locatar> locatari = service.sortare(2);
    assert(locatari[0].get_sup() == 50);
    assert(locatari[1].get_sup() == 60);
    assert(locatari[2].get_sup() == 70);
}

void test_adauga_not() {
    LocatarRepo repo;
    Locatar locatar(10, "Dan", 200, "decomandat");
    Locatar locatar1(8, "Maria", 100, "garsoniera");
    Locatar locatar2(1, "Ana", 200, "decomandat");
    repo.adauga_repo(locatar);
    repo.adauga_repo(locatar1);
    repo.adauga_repo(locatar2);
    Notificare notificare = Notificare(repo);
    notificare.adauga(8);
    assert(notificare.dim() == 1);
}

void test_goleste_not() {
    LocatarRepo repo;
    Locatar locatar(10, "Dan", 200, "decomandat");
    Locatar locatar1(8, "Maria", 100, "garsoniera");
    Locatar locatar2(1, "Ana", 200, "decomandat");
    repo.adauga_repo(locatar);
    repo.adauga_repo(locatar1);
    repo.adauga_repo(locatar2);
    Notificare notificare = Notificare(repo);
    notificare.adauga(8);
    notificare.goleste();
    assert(notificare.dim() == 0);
}

void test_gen_random_not() {
    LocatarRepo repo;
    Locatar locatar(10, "Dan", 200, "decomandat");
    Locatar locatar1(8, "Maria", 100, "garsoniera");
    Locatar locatar2(1, "Ana", 200, "decomandat");
    repo.adauga_repo(locatar);
    repo.adauga_repo(locatar1);
    repo.adauga_repo(locatar2);
    Notificare notificare = Notificare(repo);
    notificare.genereaza_random(2);
    assert(notificare.dim() == 2);
}

void test_undo_adaugare()
{
    LocatarRepo repo;
    Validator valid;
    LocatarService service = LocatarService(repo, valid);
    service.adauga_srv(1, "Ema", 50, "decomandat");
    vector<Locatar> locatari = service.get_all_srv();
    assert(locatari.size() == 1);
    service.undo();
    vector<Locatar> locatari1 = service.get_all_srv();
    assert(locatari1.empty());
}

void test_undo_modificare()
{
    LocatarRepo repo;
    Validator valid;
    LocatarService service = LocatarService(repo, valid);
    service.adauga_srv(1, "Ema", 50, "decomandat");
    service.modifica_srv(1, "Maria", 100, "garsoniera");
    vector<Locatar> locatari = service.get_all_srv();
    assert(locatari[0].get_nume() == "Maria");
    assert(locatari[0].get_sup() == 100);
    assert(locatari[0].get_tip() == "garsoniera");
    service.undo();
    vector<Locatar> locatari1 = service.get_all_srv();
    assert(locatari1[0].get_nume() == "Ema");
    assert(locatari1[0].get_sup() == 50);
    assert(locatari1[0].get_tip() == "decomandat");

}

void test_undo_stergere()
{
    LocatarRepo repo;
    Validator valid;
    LocatarService service = LocatarService(repo, valid);
    service.adauga_srv(1, "Ema", 50, "decomandat");
    vector<Locatar> locatari = service.get_all_srv();
    assert(locatari.size() == 1);
    service.sterge_srv(1);
    vector<Locatar> locatari1 = service.get_all_srv();
    assert(locatari1.empty());
    service.undo();
    vector<Locatar> locatari2 = service.get_all_srv();
    assert(locatari2.size() == 1);
}

void test_repo_file()
{
    ofstream out("locatar_test.txt");
    out.close();
    FileRepo repo{"locatar_test.txt"};
    repo.adauga_repo(Locatar{13,"Andrei",60,"decomandat"});
    FileRepo repo1{"locatar_test.txt"};
    auto locatar=repo1.cauta_repo(13);
    assert(locatar.get_nume()=="Andrei");
    try{
        repo1.cauta_repo(16);
        assert(false);
    }
    catch(RepoExceptii&){}
    repo1.sterge_repo(13);
    assert(repo1.get_all_repo().size()==0);
    try{
        repo1.sterge_repo(16);
        assert(false);
    }
    catch(RepoExceptii&){}
    FileRepo repo2{"locatar_test.txt"};
    assert(repo2.get_all_repo().size()==0);
    try{
        FileRepo repo3{"locatartest.txt"};
        assert(false);
    }
    catch(RepoExceptii&){}
}

void run_all_tests() {
    test_creeaza();
    test_validare();
    test_adauga_srv();
    test_adauga_repo();
    test_modifica_srv();
    test_modifica_repo();
    test_sterge_srv();
    test_sterge_repo();
    test_cauta_srv();
    test_cauta_repo();
    test_filtrare_tip();
    test_filtrare_sup();
    test_sortare_nume();
    test_sortare_sup();
    test_adauga_not();
    test_goleste_not();
    test_gen_random_not();
    test_undo_adaugare();
    test_undo_modificare();
    test_undo_stergere();
    test_repo_file();
}