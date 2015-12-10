extern "C"
{
#include <Python.h>
#include <frameobject.h>
}

#include "InterpreterFactory.h"
#include <QApplication>
#include <ExcelViewDialog.h>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ExcelViewDialog* dialog = new ExcelViewDialog(100, 100);
    AbstractInterpreter* interpreter = InterpreterFactory::get();
    QObject::connect(dialog, SIGNAL(run(QString)), interpreter, SLOT(run(QString)));
    QObject::connect(dialog, SIGNAL(addVariable(QString, QString)), interpreter, SLOT(addVariable(QString, QString)));
    QObject::connect(interpreter, SIGNAL(logMessage(QString)), dialog->logger(), SLOT(append(QString)));
    QObject::connect(interpreter, SIGNAL(printToFocusedCell(QString)), dialog, SLOT(printToFocusedCell(QString)));

    dialog->show();

    a.exec();
}
