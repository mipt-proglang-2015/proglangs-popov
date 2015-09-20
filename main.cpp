#include "ExcelViewDialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ExcelViewDialog dialog(10, 10);
    dialog.show();
    return a.exec();
}
