#ifndef PYTHONINTERPRETER_H
#define PYTHONINTERPRETER_H

#include <QString>

extern "C"
{
#include <Python.h>
#include <frameobject.h>
}

#include "AbstractInterpreter.h"


class PythonInterpreter: public AbstractInterpreter
{
public:   
    // InterpreterInterface interface
    void initializeInterpeter();
    void finalizeInterpreter();
    void evaluateProgram(const QString &program);

private:
    static int trace(PyObject* self, PyFrameObject* frame,
                     int what, PyObject* arg);

    static PyObject* createActorModuleWrapper();
    static PyObject* printToCell(PyObject* self, PyObject* args);

    static QMap<PyThreadState*, PythonInterpreter*> m_interpreters;
    static QMap<QString, QString> m_variables;
    static PyMethodDef methods[];
    static PyModuleDef module;

public Q_SLOTS:
    void run(const QString& program);
    void addVariable(const QString& name, const QString& value);
};

#endif // PYTHONINTERPRETER_H
