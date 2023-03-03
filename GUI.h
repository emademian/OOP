//
// Created by Ema Demian on 12.05.2022.
//

#ifndef LAB10_11_GUI_H
#define LAB10_11_GUI_H

#include <QtWidgets/QApplication>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QTableWidget>
#include <QMessageBox>
#include <QHeaderView>
#include <QGroupBox>
#include <QRadioButton>
#include <QListWidget>
#include <QPainter>
#include "LocatarService.h"
#include <vector>
#include "Notificare.h"
#include "Observer.h"
#include "MyTableModel.h"

using namespace std;

class NotifGUIViewOnly : public QWidget, public Observer {
    Notificare &notif;

    void initialize() {
        notif.addObserver(this);
    }

    void paintEvent(QPaintEvent *) override {
        QPainter painter{this};

        for (auto locatar: notif.notificari()) {
            int x, y;

            x = rand() % 400 + 1;
            y = rand() % 400 + 1;
            qDebug() << x << " " << y;
            QRectF target(x, y, 100, 94);
            QRectF source(0, 0, 732, 720);
            QImage image("locatar.jpg");

            //painter.fillRect(x,y,50,50,Qt::GlobalColor::red);

            painter.drawImage(target, image, source);

            x += 40;

        }
    }

    void update() override {
        repaint();
    }

public:
    NotifGUIViewOnly(Notificare &notif) : notif{notif} {
        initialize();
    };

    /*~NotifGUIViewOnly() {
        notif.removeObserver(this);
    }*/
};

class NotifGUI : public QWidget, public Observer {
private:
    Notificare &notif;
    QHBoxLayout *main_layout = new QHBoxLayout;

    QVBoxLayout *left_screen_layout = new QVBoxLayout;
    QVBoxLayout *right_screen_layout = new QVBoxLayout;

    QPushButton *golire_button = new QPushButton("Goleste lista");

    QFormLayout *form_apartament = new QFormLayout;
    QLineEdit *text_numar_apartament = new QLineEdit;
    QPushButton *add_button = new QPushButton("Adauga");

    QFormLayout *form_numar_generare = new QFormLayout;
    QLineEdit *text_numar_generare = new QLineEdit;
    QPushButton *generate_button = new QPushButton("Genereaza lista");

    QFormLayout *form_nume_fisier = new QFormLayout;
    QLineEdit *text_nume_fisier = new QLineEdit;
    QPushButton *export_button = new QPushButton("Export in fisier");

    QListWidget *lista_notificari = new QListWidget;

    QPushButton *exit_button = new QPushButton("&Exit");

    void initializare();

    void conexiuni();

    void load_lista_notificari(const vector<Locatar> &notificari);

    void update() override {
        load_lista_notificari(notif.notificari());
    }

public:
    NotifGUI(Notificare &notif) : notif{notif} {
        initializare();
        conexiuni();
    }

};


class GUI : public QWidget {
private:
    LocatarService &srv;
    Notificare &notif;
    NotifGUI notifGUI{notif};
    NotifGUIViewOnly notifGUIview{notif};
    //ModelGUI modelGUI{srv};
    //etichete
    QLabel *lblAp;
    QLabel *lblNume;
    QLabel *lblSuprafata;
    QLabel *lblTip;
    //casute
    QLineEdit *editAp;
    QLineEdit *editNume;
    QLineEdit *editSuprafata;
    QLineEdit *editTip;
    //butoane
    QPushButton *btnAddLocatar;
    QPushButton *btnModificare;
    QPushButton *btnStergere;

    QLabel *lblStergere = new QLabel{"Apartament:"};
    QLineEdit *editStergere;


    QGroupBox *groupBox = new QGroupBox(tr("Sortare"));

    QRadioButton *radioSrtNume = new QRadioButton(QString::fromStdString("Nume"));
    QRadioButton *radioSrtSuprafata = new QRadioButton(QString::fromStdString("Suprafata"));
    QPushButton *btnSortLocatari;

    QLabel *lblFilterCriteria = new QLabel{"Tip dupa care se filtreaza:"};
    QLineEdit *editFilterTip;
    QPushButton *btnFilterLocatari;
    QLabel *lblFilterCriteria2 = new QLabel{"Suprafata dupa care se filtreaza:"};
    QLineEdit *editFilterTip2;
    QPushButton *btnFilterLocatari2;

    QPushButton *btnUndo;
    QPushButton *btnReloadData;

    QTableWidget *tableLocatari;

    QPushButton *btnExit = new QPushButton;

    QPushButton *btnNotif = new QPushButton;
    QPushButton *btnNotifView = new QPushButton;

    MyTableModel* model;
    QTableView* tblView;


    void init_GUI_comp();

    void connect_signal_slots();

    void reload_list(const vector<Locatar> &locatari);


public:
    GUI(LocatarService &srv, Notificare &notif) : srv{srv}, notif{notif} {
        init_GUI_comp();
        connect_signal_slots();
        reload_list(srv.get_all_srv());
    }

    void adauga_locatar_gui();

    void modifica_locatar_gui();

    void sterge_locatar_gui();

};




#endif //LAB10_11_GUI_H
