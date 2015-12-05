#ifndef ACTOR_H
#define ACTOR_H

#include <QWidget>
#include "ExcelViewDialog.h"

class Actor: public QWidget
{
    Q_OBJECT
public:
    explicit Actor(QWidget *parent = 0);
    void setExcelView(ExcelViewDialog* excelView);
    void printToCell(QString text);
    ~Actor();

private:
    ExcelViewDialog* excelView_;
};

#endif // ACTOR_H
