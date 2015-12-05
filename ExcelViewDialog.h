#ifndef EXCELVIEWDIALOG_H
#define EXCELVIEWDIALOG_H

#include <QDialog>
#include <QTableWidget>
#include <QTextBrowser>
#include <QTextEdit>

namespace Ui
{
    class ExcelViewDialog;
}

class ExcelViewDialog : public QDialog
{
    Q_OBJECT

public:
    ExcelViewDialog(int row_count, int column_count, QWidget *parent = 0);
    QTextBrowser* cellNameView();
    QTextEdit* cellValueView();

    ~ExcelViewDialog();

private:
    void initHeaderLabels();
    void initCellItems();
    QString getHeaderLabel(int index) const;

public Q_SLOTS:
    void cellPressed(int row, int column);
    void cellChanged(int row, int column);
    void valueViewTextChanged();


private:
    Ui::ExcelViewDialog* ui_;
    QTableWidget* tableWidget_;
    QTextBrowser* nameView_;
    QTextEdit* valueView_;
};

#endif // EXCELVIEWDIALOG_H
