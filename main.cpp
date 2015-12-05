#include "ExcelViewDialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ExcelViewDialog* dialog = new ExcelViewDialog(100, 100);
    dialog->show();
    a.exec();
}
