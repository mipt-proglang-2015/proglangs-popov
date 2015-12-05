extern "C"
{
#include <Python.h>
#include <frameobject.h>
}

#include "Actor.h"
#include "InterpreterFactory.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ExcelViewDialog* dialog = new ExcelViewDialog(100, 100);
    Actor* actor = new Actor();
    AbstractInterpreter* interpreter = InterpreterFactory::get();
    interpreter->setActor(actor);
    actor->setExcelView(dialog);
    QObject::connect(dialog, SIGNAL(run(QString)), interpreter, SLOT(run(QString)));
    QObject::connect(interpreter, SIGNAL(logMessage(QString)), dialog->logger(), SLOT(append(QString)));
    dialog->show();

    a.exec();
}
