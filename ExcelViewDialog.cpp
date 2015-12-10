#include "ExcelViewDialog.h"
#include "ui_ExcelViewDialog.h"
#include "Constants.h"
#include <iostream>

ExcelViewDialog::ExcelViewDialog(int row_count, int column_count, QWidget *parent) :
    QDialog(parent), ui_(new Ui::ExcelViewDialog)
{
    ui_->setupUi(this);

    tableWidget_ = ui_->tableWidget;

    nameView_ = ui_->cellNameView;

    logger_ = ui_->loggerView;

    tableWidget_->setRowCount(row_count);

    tableWidget_->setColumnCount(column_count);

    initCellItems();

    initHeaderLabels();

    QObject::connect(tableWidget_, SIGNAL(cellPressed(int,int)), this, SLOT(cellPressed(int, int)));
    QObject::connect(tableWidget_, SIGNAL(cellEntered(int,int)), this, SLOT(cellPressed(int, int)));
    QObject::connect(tableWidget_, SIGNAL(cellChanged(int, int)), this, SLOT(cellChanged(int, int)));
}

QTextBrowser* ExcelViewDialog::cellNameView() const
{
    return nameView_;
}

QTextBrowser* ExcelViewDialog::logger() const
{
    return logger_;
}

QTableWidget* ExcelViewDialog::tableWidget() const
{
    return tableWidget_;
}

ExcelViewDialog::~ExcelViewDialog()
{
    delete ui_;
}

void ExcelViewDialog::initHeaderLabels()
{
    QStringList labels;
    for (int index = 0; index < tableWidget_->columnCount(); ++index)
    {
        labels.append(getHeaderLabel(index));
    }
    tableWidget_->setHorizontalHeaderLabels(labels);
}

void ExcelViewDialog::initCellItems()
{
    for (int rowIndex = 0; rowIndex < tableWidget_->rowCount(); ++rowIndex)
    {
        for (int columnIndex = 0; columnIndex < tableWidget_->columnCount(); ++columnIndex)
        {
            tableWidget_->setItem(rowIndex, columnIndex, new QTableWidgetItem(""));
        }
    }
}

QString ExcelViewDialog::getHeaderLabel(int index) const
{
    int current_section = index;
    QString columnName = "";
    while (current_section >= 0)
    {
        columnName += ('A' + current_section % ALPHABET_SIZE);
        current_section /= ALPHABET_SIZE;
        --current_section;
    }
    std::reverse(columnName.begin(), columnName.end());
    return columnName;
}

void ExcelViewDialog::cellPressed(int row, int column)
{
    nameView_->setText(getHeaderLabel(column) + QString::number(row + 1));
}

void ExcelViewDialog::cellChanged(int row, int column)
{
    const QString text = tableWidget_->item(row, column)->text();
    if(text.at(0) == '=')
    {
        const QString programm = text.mid(1);
        emit run(programm);
    }
    emit addVariable(getHeaderLabel(column) + QString::number(row + 1), tableWidget_->currentItem()->text());
}

void ExcelViewDialog::printToFocusedCell(const QString &text)
{
    QObject::disconnect(tableWidget_, SIGNAL(cellChanged(int, int)),
                        this, SLOT(cellChanged(int, int)));
    tableWidget_->currentItem()->setText(text);
    QObject::connect(tableWidget_, SIGNAL(cellChanged(int, int)),
                     this, SLOT(cellChanged(int, int)));
}

