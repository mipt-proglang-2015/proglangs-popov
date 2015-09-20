#include "ExcelViewDialog.h"
#include "ui_ExcelViewDialog.h"

ExcelViewDialog::ExcelViewDialog(int row_count, int column_count, QWidget *parent) :
    QDialog(parent), ui_(new Ui::ExcelViewDialog)
{
    ui_->setupUi(this);
    // Create a new custom model
    model_ = new ExcelModel(row_count, column_count);
    // Attach the model to the view
    ui_->tableView->setModel(model_);

}

ExcelViewDialog::~ExcelViewDialog()
{
    delete ui_;
}
