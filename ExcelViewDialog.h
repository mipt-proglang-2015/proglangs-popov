#ifndef EXCELVIEWDIALOG_H
#define EXCELVIEWDIALOG_H

#include "ExcelModel.h"

#include <QDialog>
#include <QTableView>
#include <QItemDelegate>

namespace Ui {
    class ExcelViewDialog;
}

class ExcelViewDialog : public QDialog
{
    Q_OBJECT

public:
    ExcelViewDialog(int row_count, int column_count, QWidget *parent = 0);

    ~ExcelViewDialog();

private:
    Ui::ExcelViewDialog *ui_;

    ExcelModel *model_;
};

#endif // EXCELVIEWDIALOG_H
