#ifndef EXCELMODEL_H
#define EXCELMODEL_H

#include <QAbstractTableModel>

class ExcelModel : public QAbstractTableModel
{
    Q_OBJECT

    static const int ALPHABET_SIZE = 26;

public:
    ExcelModel(int row_count, int column_count, QObject *parent = 0);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

    Qt::ItemFlags flags(const QModelIndex &index) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

private:
    QString getRowName(int section) const;

    QString getColumnName(int sectiom) const;

private:
    QVector<QVector<QString> > data_storage_; //holds text entered into QTableView

    int row_count_;

    int column_count_;
};

#endif // EXCELMODEL_H
