#include "ExcelModel.h"

ExcelModel::ExcelModel(int row_count, int column_count, QObject *parent) :
    QAbstractTableModel(parent), row_count_(row_count), column_count_(column_count)
{
    data_storage_ = QVector<QVector<QString> >(row_count, QVector<QString>(column_count));
}

int ExcelModel::rowCount(const QModelIndex & /*parent*/) const
{
   return row_count_;
}

int ExcelModel::columnCount(const QModelIndex & /*parent*/) const
{
    return column_count_;
}

QVariant ExcelModel::data(const QModelIndex & index, int role) const
{
    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        return data_storage_[index.row()][index.column()];
    }
    return QVariant();
}

bool ExcelModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole) {
        // save value from editor to member data_storage_
        data_storage_[index.row()][index.column()] = value.toString();
        emit dataChanged(index, index);
    } else {
        return false;
    }
    return true;
}

Qt::ItemFlags ExcelModel::flags(const QModelIndex & /*index*/) const
{
    return Qt::ItemIsSelectable |  Qt::ItemIsEditable | Qt::ItemIsEnabled ;
}


QString ExcelModel::getColumnName(int section) const
{
    int current_section = section;
    QString columnName = "";
    while (current_section >= 0) {
        columnName += ('A' + current_section % ALPHABET_SIZE);
        current_section /= ALPHABET_SIZE;
        current_section--;
    }
    // columnName += ('A' + current_section);
    std::reverse(columnName.begin(), columnName.end());
    return columnName;
}

QString ExcelModel::getRowName(int section) const
{
    return QString::number(section + 1);
}

QVariant ExcelModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal) {
            return getColumnName(section);
        } else {
            return getRowName(section);
        }
    } else if (role == Qt::TextAlignmentRole) {
        if (orientation == Qt::Vertical) {
            return Qt::AlignCenter;
        }
    }
    return QVariant();
}
