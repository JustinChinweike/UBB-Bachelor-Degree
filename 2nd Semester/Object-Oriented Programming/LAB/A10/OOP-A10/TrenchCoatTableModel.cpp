// TrenchCoatTableModel.cpp
#include "TrenchCoatTableModel.h"

TrenchCoatTableModel::TrenchCoatTableModel(QObject* parent) 
    
    : QAbstractTableModel(parent) {}



int TrenchCoatTableModel::rowCount(const QModelIndex& parent) const {
    return trenchCoats.size();
}

int TrenchCoatTableModel::columnCount(const QModelIndex& parent) const {
    return 6; // ID, Size, Colour, Price, Quantity, Photograph
}

QVariant TrenchCoatTableModel::data(const QModelIndex& index, int role) const {
    if (role == Qt::DisplayRole) {
        const TrenchCoat& trenchCoat = trenchCoats[index.row()];
        switch (index.column()) {
        case 0: return trenchCoat.getTrenchID();
        case 1: return trenchCoat.getTrenchSize();
        case 2: return QString::fromStdString(trenchCoat.getTrenchColour());
        case 3: return trenchCoat.getTrenchPrice();
        case 4: return trenchCoat.getTrenchQuantity();
        case 5: return QString::fromStdString(trenchCoat.getTrenchPhotographyLink());
        }
    }
    return QVariant();
}


QVariant TrenchCoatTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal) {
            switch (section) {
            case 0: return QString("ID");
            case 1: return QString("Size");
            case 2: return QString("Colour");
            case 3: return QString("Price");
            case 4: return QString("Quantity");
            case 5: return QString("Photograph");
            }
        }
    }
    return QVariant();
}


void TrenchCoatTableModel::setTrenchCoats(const std::vector<TrenchCoat>& trenchCoats) {
    beginResetModel();
    this->trenchCoats = trenchCoats;
    endResetModel();
}


//void TrenchCoatTableModel::setTrenchCoats(const std::vector<TrenchCoat>& trenchCoats) {
//    this->trenchCoats = trenchCoats;
//    emit dataChanged(index(0, 0), index(rowCount() - 1, columnCount() - 1));
//}