#include <iostream>
#include "Console.h"
#include "Teste.h"
#include "FileRepo.h"
#include "GUI.h"

using namespace std;


int main(int argc, char* argv[]) {
    run_all_tests();
    cout << "Finish tests" << endl;
    QApplication app(argc, argv);
    //LocatarRepo repo;
    FileRepo repo{"locatari.txt"};
    Validator valid;
    LocatarService service = LocatarService(repo, valid);
    Notificare notificare = Notificare(repo);
    /*Console console = Console(service, notificare);
    console.run_console();*/

    GUI gui=GUI(service,notificare);
    //ModelGUI gui=ModelGUI(service);
    gui.show();
    return app.exec();

}
