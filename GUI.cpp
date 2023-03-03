#include "GUI.h"

void GUI::init_GUI_comp() {
    QHBoxLayout *lyMain = new QHBoxLayout(this);
    //this->setLayout(lyMain);

    QWidget *left = new QWidget;
    QVBoxLayout *lyLeft = new QVBoxLayout;
    //left->setLayout(lyLeft);

    QWidget *right = new QWidget;
    QVBoxLayout *lyRight = new QVBoxLayout;
    //right->setLayout(lyRight);

    lblAp = new QLabel{ "Apartament:" };
    lblNume = new QLabel{ "Nume:" };
    lblSuprafata = new QLabel{ "Suprafata:" };
    lblTip = new QLabel{ "Tip:" };

    QWidget *form = new QWidget;
    QFormLayout *lyForm = new QFormLayout;
    form->setLayout(lyForm);
    editAp = new QLineEdit;
    editNume = new QLineEdit;
    editSuprafata = new QLineEdit;
    editTip = new QLineEdit;

    lyForm->addRow(lblAp, editAp);
    lyForm->addRow(lblNume, editNume);
    lyForm->addRow(lblSuprafata, editSuprafata);
    lyForm->addRow(lblTip, editTip);
    btnAddLocatar = new QPushButton("Adauga locatar");
    lyForm->addWidget(btnAddLocatar);
    btnModificare = new QPushButton("Modifica locatar");
    lyForm->addWidget(btnModificare);

    lyLeft->addWidget(form);

    QWidget *formStergere = new QWidget;
    QFormLayout *lyFormStergere = new QFormLayout;
    formStergere->setLayout(lyFormStergere);
    editStergere = new QLineEdit();
    btnStergere = new QPushButton("Sterge locatar");
    lyFormStergere->addRow(lblStergere, editStergere);
    lyFormStergere->addWidget(btnStergere);
    lyLeft->addWidget(formStergere);

    QVBoxLayout *lyRadioBox = new QVBoxLayout;
    this->groupBox->setLayout(lyRadioBox);
    lyRadioBox->addWidget(radioSrtNume);
    lyRadioBox->addWidget(radioSrtSuprafata);

    btnSortLocatari = new QPushButton("Sorteaza locatari");
    lyRadioBox->addWidget(btnSortLocatari);

    lyLeft->addWidget(groupBox);

    QWidget *formFilter = new QWidget;
    QFormLayout *lyFormFilter = new QFormLayout;
    formFilter->setLayout(lyFormFilter);
    editFilterTip = new QLineEdit();
    lyFormFilter->addRow(lblFilterCriteria, editFilterTip);
    btnFilterLocatari = new QPushButton("Filtreaza locatari dupa tip");
    lyFormFilter->addWidget(btnFilterLocatari);
    lyLeft->addWidget(formFilter);

    QWidget *formFilter2 = new QWidget;
    QFormLayout *lyFormFilter2 = new QFormLayout;
    formFilter2->setLayout(lyFormFilter2);
    editFilterTip2 = new QLineEdit();
    lyFormFilter2->addRow(lblFilterCriteria2, editFilterTip2);
    btnFilterLocatari2 = new QPushButton("Filtreaza locatari dupa suprafata");
    lyFormFilter2->addWidget(btnFilterLocatari2);
    lyLeft->addWidget(formFilter2);

    btnUndo = new QPushButton("Undo");
    lyLeft->addWidget(btnUndo);


    int noLines = 10;
    int noColumns = 4;
    this->tableLocatari = new QTableWidget{noLines, noColumns};

    QStringList tblHeaderList;
    tblHeaderList << "Apartament" << "Nume" << "Suprafata" << "Tip";
    this->tableLocatari->setHorizontalHeaderLabels(tblHeaderList);

    this->tableLocatari->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    lyRight->addWidget(tableLocatari);


    btnReloadData = new QPushButton("Reload data");
    lyRight->addWidget(btnReloadData);

    btnNotif = new QPushButton("Notificari");
    lyRight->addWidget(btnNotif);

    btnNotifView = new QPushButton("Notificari View");
    lyRight->addWidget(btnNotifView);

    btnExit = new QPushButton("Exit");
    lyRight->addWidget(btnExit);


    model=new MyTableModel(srv.get_all_srv());
    tblView = new QTableView;
    tblView->setModel(model);
    lyRight->addWidget(tblView);

    lyMain->addLayout(lyLeft);
    lyMain->addLayout(lyRight);
}

void GUI::connect_signal_slots() {
    QObject::connect(btnAddLocatar, &QPushButton::clicked, this, &GUI::adauga_locatar_gui);
    QObject::connect(btnStergere, &QPushButton::clicked, this, &GUI::sterge_locatar_gui);
    QObject::connect(btnModificare, &QPushButton::clicked, this, &GUI::modifica_locatar_gui);
    QObject::connect(btnSortLocatari, &QPushButton::clicked, [&]() {
        if (this->radioSrtNume->isChecked())
            this->reload_list(srv.sortare(1));
        else if (this->radioSrtSuprafata->isChecked())
            this->reload_list(srv.sortare(2));
    });

    QObject::connect(btnFilterLocatari, &QPushButton::clicked, [&]() {
        string filterC = this->editFilterTip->text().toStdString();
        this->reload_list(srv.filtrare_tip(filterC));
    });

    QObject::connect(btnFilterLocatari2, &QPushButton::clicked, [&]() {
        int filterC2 = this->editFilterTip2->text().toInt();
        this->reload_list(srv.filtrare_sup(filterC2));
    });

    QObject::connect(btnReloadData, &QPushButton::clicked, [&]() {
        this->reload_list(srv.get_all_srv());
    });
    QObject::connect(btnUndo, &QPushButton::clicked, [&]() {
        srv.undo();
        this->reload_list(srv.get_all_srv());
    });
    QObject::connect(btnNotif, &QPushButton::clicked, [&]() {
        notifGUI.show();
    });
    QObject::connect(btnNotifView, &QPushButton::clicked, [&]() {
        notifGUIview.show();
    });
    QObject::connect(btnExit, &QPushButton::clicked, [&]() {
        close();
    });
}

void GUI::reload_list(const vector<Locatar> &locatari) {
    this->tableLocatari->clear();
    this->tableLocatari->setRowCount(locatari.size());

    int lineNumber = 0;
    for (auto &locatar: locatari) {
        this->tableLocatari->setItem(lineNumber, 0, new QTableWidgetItem(QString::number(locatar.get_ap())));
        this->tableLocatari->setItem(lineNumber, 1, new QTableWidgetItem(QString::fromStdString(locatar.get_nume())));
        this->tableLocatari->setItem(lineNumber, 2, new QTableWidgetItem(QString::number(locatar.get_sup())));
        this->tableLocatari->setItem(lineNumber, 3, new QTableWidgetItem(QString::fromStdString(locatar.get_tip())));
        lineNumber++;
    }
    model->setLocatari(locatari);
}

void GUI::adauga_locatar_gui() {

    int ap = editAp->text().toInt();
    string nume = editNume->text().toStdString();
    int suprafata = editSuprafata->text().toInt();
    string tip = editTip->text().toStdString();

    editAp->clear();
    editNume->clear();
    editSuprafata->clear();
    editTip->clear();

    this->srv.adauga_srv(ap, nume, suprafata, tip);
    this->reload_list(this->srv.get_all_srv());

}

void GUI::sterge_locatar_gui() {
    int ap = editStergere->text().toInt();
    editStergere->clear();
    this->srv.sterge_srv(ap);
    this->reload_list(this->srv.get_all_srv());

}

void GUI::modifica_locatar_gui() {

    int ap = editAp->text().toInt();
    string nume = editNume->text().toStdString();
    int suprafata = editSuprafata->text().toInt();
    string tip = editTip->text().toStdString();

    editAp->clear();
    editNume->clear();
    editSuprafata->clear();
    editTip->clear();

    this->srv.modifica_srv(ap, nume, suprafata, tip);
    this->reload_list(this->srv.get_all_srv());

}

void NotifGUI::initializare() {
    setLayout(main_layout);

    form_apartament->addRow("Numar apartament:", text_numar_apartament);
    left_screen_layout->addLayout(form_apartament);
    left_screen_layout->addWidget(add_button);

    form_numar_generare->addRow("Numar locatari de generat:", text_numar_generare);
    left_screen_layout->addLayout(form_numar_generare);
    left_screen_layout->addWidget(generate_button);

    form_nume_fisier->addRow("Nume fisier:", text_nume_fisier);
    left_screen_layout->addLayout(form_nume_fisier);
    left_screen_layout->addWidget(export_button);

    left_screen_layout->addWidget(golire_button);

    main_layout->addLayout(left_screen_layout);

    right_screen_layout->addWidget(lista_notificari);
    right_screen_layout->addWidget(exit_button);

    main_layout->addLayout(right_screen_layout);

}

void NotifGUI::conexiuni() {
    QObject::connect(exit_button, &QPushButton::clicked, [&]() {
        close();
    });

    QObject::connect(add_button, &QPushButton::clicked, [&]() {
        auto apartament_text = text_numar_apartament->text();

        int apartament;
        string string_apartament = apartament_text.toStdString();
        apartament = stoi(string_apartament);
        notif.adauga(apartament);
        load_lista_notificari(notif.notificari());
    });


    QObject::connect(generate_button, &QPushButton::clicked, [&]() {
        auto numar_text = text_numar_generare->text();
        int numar_de_generat;
        string string_numar = numar_text.toStdString();
        numar_de_generat = stoi(string_numar);
        notif.genereaza_random(numar_de_generat);
        load_lista_notificari(notif.notificari());
    });

    QObject::connect(golire_button, &QPushButton::clicked, [&]() {
        notif.goleste();
        load_lista_notificari(notif.notificari());

    });


}

void NotifGUI::load_lista_notificari(const vector<Locatar> &locatari) {
    lista_notificari->clear();
    for (const auto &locatar: locatari) {
        QListWidgetItem *item = new QListWidgetItem(QString::fromStdString(
                "Numar apartament: " + to_string(locatar.get_ap()) + ", Nume locatar: " + locatar.get_nume()));
        lista_notificari->addItem(item);
    }
}
/*
void ModelGUI::initialize() {
    QHBoxLayout* ly = new QHBoxLayout;
    setLayout(ly);

    //adaug lista si sub doua butoane de sort
    QWidget* widDreapta = new QWidget;
    QVBoxLayout* vl = new QVBoxLayout;
    widDreapta->setLayout(vl);

    lstView = new QListView;
    lstView->setUniformItemSizes(true);
    vl->addWidget(lstView);


    QWidget* widBtnDreapta = new QWidget;
    QHBoxLayout* lyBtnsDr = new QHBoxLayout;
    widBtnDreapta->setLayout(lyBtnsDr);

    vl->addWidget(widBtnDreapta);
    ly->addWidget(widDreapta);

    QWidget* widDreapta2 = new QWidget;
    QVBoxLayout *lyDreapta = new QVBoxLayout;
    widDreapta2->setLayout(lyDreapta);

    //fac un form pentru detalii
    QWidget* widDetalii = new QWidget;
    QFormLayout* formLDetalii = new QFormLayout;
    widDetalii->setLayout(formLDetalii);
    editAp = new QLineEdit;
    formLDetalii->addRow(new QLabel("Apartament:"), editAp);
    editNume = new QLineEdit;
    formLDetalii->addRow(new QLabel("Nume:"), editNume);
    editSuprafata = new QLineEdit;
    formLDetalii->addRow(new QLabel("Suprafata:"), editSuprafata);
    editTip = new QLineEdit;
    formLDetalii->addRow(new QLabel("Tip:"), editTip);

    ly->addWidget(widDreapta2);

    ly->addWidget(tblView);
}

void ModelGUI::connect() {
    QObject::connect(tblView->selectionModel(), &QItemSelectionModel::selectionChanged, [this]() {
        if (tblView->selectionModel()->selectedIndexes().isEmpty()) {
            editAp->setText("");
            editNume->setText("");
            editSuprafata->setText("");
            editTip->setText("");
            return;
        }
        int selRow = tblView->selectionModel()->selectedIndexes().at(0).row();
        auto cel0Index = tblView->model()->index(selRow, 0);
        auto cel0Value= tblView->model()->data(cel0Index, Qt::DisplayRole).toString();
        editAp->setText(cel0Value);
        auto cel1Index = tblView->model()->index(selRow, 1);
        auto cel1Value = tblView->model()->data(cel1Index, Qt::DisplayRole).toString();
        editNume->setText(cel1Value);
        auto cel2Index = tblView->model()->index(selRow, 2);
        auto cel2Value = tblView->model()->data(cel2Index, Qt::DisplayRole).toString();
        editSuprafata->setText(cel2Value);
        auto cel3Index = tblView->model()->index(selRow, 3);
        auto cel3Value = tblView->model()->data(cel3Index, Qt::DisplayRole).toString();
        editTip->setText(cel3Value);
    });
}

void ModelGUI::reload_list(const vector<Locatar> &locatari) {
    model->setLocatari(locatari);
}*/
