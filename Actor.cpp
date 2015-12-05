#include "Actor.h"
#include <iostream>

Actor::Actor(QWidget *parent): QWidget(parent)
{
}

void Actor::setExcelView(ExcelViewDialog* excelView)
{
    excelView_ = excelView;
}

Actor::~Actor()
{
}

void Actor::printToCell(QString text)
{
    QObject::disconnect(excelView_->tableWidget(), SIGNAL(cellChanged(int, int)),
                        excelView_, SLOT(cellChanged(int, int)));
    excelView_->tableWidget()->currentItem()->setText(text);
    QObject::connect(excelView_->tableWidget(), SIGNAL(cellChanged(int, int)),
                     excelView_, SLOT(cellChanged(int, int)));
}
