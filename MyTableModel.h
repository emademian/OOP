//
// Created by Ema Demian on 27.05.2022.
//

#ifndef LAB10_11_MYTABLEMODEL_H
#define LAB10_11_MYTABLEMODEL_H

#include <QAbstractTableModel>
#include "Locatar.h"
#include <vector>
#include <qdebug.h>
#include<QBrush>

class MyTableModel : public QAbstractTableModel {
    std::vector<Locatar> locatari;
public:
    MyTableModel(const std::vector<Locatar> &locatari) : locatari{locatari} {
    }

    int rowCount(const QModelIndex &parent = QModelIndex()) const override {
        return locatari.size();
    }

    int columnCount(const QModelIndex &parent = QModelIndex()) const override {
        return 4;
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override {
        //qDebug() << "row:" << index.row() << " col:" << index.column() << " role" << role;
        if (role == Qt::ForegroundRole) {
            Locatar locatar = locatari[index.row()];
            if (locatar.get_tip()=="decomandat") {
                return QBrush{Qt::red};
            }
            else if (locatar.get_tip()=="garsoniera"){
                return QBrush{Qt::yellow};
            }
            else if(locatar.get_tip()=="studio"){
                return QBrush{Qt::green};
            }
        }
        if (role == Qt::DisplayRole) {

            Locatar locatar = locatari[index.row()];
            if (index.column() == 0) {
                return QString::number(locatar.get_ap());
            } else if (index.column() == 1) {
                return QString::fromStdString(locatar.get_nume());
            } else if (index.column() == 2) {
                return QString::number(locatar.get_sup());
            } else if (index.column() == 3) {
                return QString::fromStdString(locatar.get_tip());
            }
        }

        return QVariant{};
    }

    void setLocatari(const vector<Locatar> &locatari) {
        this->locatari = locatari;
        auto topLeft = createIndex(0, 0);
        auto bottomR = createIndex(rowCount(), columnCount());
        emit dataChanged(topLeft, bottomR);
    }
};

#endif //LAB10_11_MYTABLEMODEL_H
