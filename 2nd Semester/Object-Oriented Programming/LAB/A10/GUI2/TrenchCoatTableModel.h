#include "Domain.h"
#include <QAbstractTableModel>
#include <vector>


class TrenchCoatTableModel : public QAbstractTableModel {
    Q_OBJECT

private:
    std::vector<TrenchCoat>& trenchCoats;

public:
    explicit TrenchCoatTableModel(std::vector<TrenchCoat>& trenchCoats, QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
};