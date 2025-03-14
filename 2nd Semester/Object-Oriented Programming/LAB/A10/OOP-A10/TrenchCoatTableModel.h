#pragma once

#include <QAbstractTableModel>
#include <Domain.h>



class TrenchCoatTableModel  : public QAbstractTableModel
{
    	Q_OBJECT

private:
    std::vector<TrenchCoat> trenchCoats;

public:
    TrenchCoatTableModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    void setTrenchCoats(const std::vector<TrenchCoat>& trenchCoats);
};
