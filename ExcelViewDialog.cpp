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

    valueView_ = ui_->cellValueView;

    tableWidget_->setRowCount(row_count);

    tableWidget_->setColumnCount(column_count);

    initCellItems();

    initHeaderLabels();

    QObject::connect(tableWidget_, SIGNAL(cellPressed(int,int)), this, SLOT(cellPressed(int, int)));
    QObject::connect(tableWidget_, SIGNAL(cellEntered(int,int)), this, SLOT(cellPressed(int, int)));
    QObject::connect(tableWidget_, SIGNAL(cellChanged(int, int)), this, SLOT(cellChanged(int, int)));
    QObject::connect(valueView_, SIGNAL(textChanged()), this, SLOT(valueViewTextChanged()));
}

QTextBrowser* ExcelViewDialog::cellNameView()
{
    return nameView_;
}

QTextEdit* ExcelViewDialog::cellValueView()
{
    return valueView_;
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
    nameView_->setText(getHeaderLabel(column));
}

void ExcelViewDialog::cellChanged(int row, int column)
{
    valueView_->setText(tableWidget_->item(row, column)->text());
}

void ExcelViewDialog::valueViewTextChanged()
{
    QObject::disconnect(tableWidget_, SIGNAL(cellChanged(int, int)), this, SLOT(cellChanged(int, int)));
    tableWidget_->currentItem()->setText(valueView_->toPlainText());
    QObject::connect(tableWidget_, SIGNAL(cellChanged(int, int)), this, SLOT(cellChanged(int, int)));
}
