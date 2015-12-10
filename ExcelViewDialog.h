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
    QTextBrowser* cellNameView() const;
    QTextBrowser* logger() const;
    QTableWidget* tableWidget() const;

    ~ExcelViewDialog();

private:
    void initHeaderLabels();
    void initCellItems();
    QString getHeaderLabel(int index) const;

public Q_SLOTS:
    void cellPressed(int row, int column);
    void cellChanged(int row, int column);
    void printToFocusedCell(const QString& text);

Q_SIGNALS:
    void run(const QString& message);
    void addVariable(const QString& name, const QString& value);


private:
    Ui::ExcelViewDialog* ui_;
    QTableWidget* tableWidget_;
    QTextBrowser* nameView_;
    QTextBrowser* logger_;
};

#endif // EXCELVIEWDIALOG_H
