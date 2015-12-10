#include "PythonInterpreter.h"
#include "InterpreterFactory.h"

#include <QCoreApplication>
#include <QDir>
#include <iostream>


void PythonInterpreter::initializeInterpeter()
{
    Py_Initialize();
    mainModule = PyImport_AddModule("__main__");
    moduleDict = PyModule_GetDict(mainModule);
    QMapIterator<QString, PyObject*> iterator(m_variables);
    while (iterator.hasNext())
    {
        iterator.next();
        PyObject* Variabe = iterator.value();
        Py_INCREF(Variabe);
        PyDict_SetItemString(moduleDict, iterator.key().toUtf8().toStdString().c_str(), Variabe);
    }
    m_interpreters[PyThreadState_Get()] = this;
    PyRun_SimpleString("from math import *\n");
    PyEval_SetTrace(trace, NULL);
}

void PythonInterpreter::finalizeInterpreter()
{
    m_interpreters.remove(PyThreadState_Get());
    Py_Finalize();
}

void PythonInterpreter::evaluateProgram(const QString &program)
{
    const QByteArray utf8_program = program.toUtf8();
    PyObject* code = Py_CompileString(utf8_program.constData() , "" , Py_eval_input);
    PyObject* result = PyEval_EvalCode(code, moduleDict, moduleDict);
    if(result)
    {
        PyObject* out = PyObject_Repr(result);
        wchar_t* out_buffer = PyUnicode_AsWideCharString(out, NULL);
        QString str = QString::fromWCharArray(out_buffer);
        emit printToFocusedCell(str);
        Py_DECREF(out);
        Py_DECREF(result);
    }
}

int PythonInterpreter::trace(PyObject*, PyFrameObject*,
                             int what, PyObject *arg)
{
    PythonInterpreter* _this = m_interpreters[PyThreadState_Get()];
    if (PyTrace_EXCEPTION == what)
    {
        PyObject* exception = PyTuple_GetItem(arg, 1);
        PyObject* message = PyObject_Repr(exception);// Сделать строковое представление объекта.
        wchar_t* msg_buffer = PyUnicode_AsWideCharString(message, NULL);
        _this->m_errorMessage = QString::fromWCharArray(msg_buffer);
        Py_DECREF(message);
        PyErr_Print();
    }
    else if(PyTrace_RETURN == what)
    {
        return 0;
    }
    return 0;
}

void PythonInterpreter::run(const QString &program)
{
    reset();
    initializeInterpeter();
    evaluateProgram(program);
    if (errorMessage().length() > 0)
    {
        emit logMessage(errorMessage() + "\n");
    }
    finalizeInterpreter();
}

void PythonInterpreter::addVariable(const QString& name, const QString& value)
{
    PyObject* objectValue;
    bool isConvertedLong;
    long longValue = value.toLong(&isConvertedLong);
    if(isConvertedLong)
    {
        objectValue = PyLong_FromLong(longValue);
    }
    else
    {
        bool isConvertedDouble;
        double doubleValue = value.toDouble(&isConvertedDouble);
        if(isConvertedDouble)
        {
            objectValue = PyFloat_FromDouble(doubleValue);
        }
        else
        {
            objectValue = PyUnicode_FromString(value.toUtf8().toStdString().c_str());
        }
    }
    m_variables.insert(name, objectValue);
}


QMap<PyThreadState*, PythonInterpreter*> PythonInterpreter::m_interpreters;
QMap<QString, PyObject*> PythonInterpreter::m_variables;
PyObject* PythonInterpreter::mainModule;
PyObject* PythonInterpreter::moduleDict;

REGISTER_INTERPRETER(PythonInterpreter)
