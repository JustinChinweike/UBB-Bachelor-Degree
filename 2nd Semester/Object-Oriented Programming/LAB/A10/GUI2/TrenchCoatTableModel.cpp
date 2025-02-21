#include "TrenchCoatTableModel.h"

TrenchCoatTableModel::TrenchCoatTableModel(std::vector<TrenchCoat>& trenchCoats, QObject* parent)
    : QAbstractTableModel(parent), trenchCoats(trenchCoats) {
}


int TrenchCoatTableModel::rowCount(const QModelIndex& parent) const {
    return trenchCoats.size();
}

int TrenchCoatTableModel::columnCount(const QModelIndex& parent) const {
    return 6;  // ID, Size, Color, Price, Quantity, Photo URL
}

QVariant TrenchCoatTableModel::data(const QModelIndex& index, int role) const {
    if (role == Qt::DisplayRole) {
        const auto& trenchCoat = trenchCoats[index.row()];
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
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case 0: return "ID";
        case 1: return "Size";
        case 2: return "Color";
        case 3: return "Price";
        case 4: return "Quantity";
        case 5: return "Photo URL";
        }
    }
    return QVariant();
}