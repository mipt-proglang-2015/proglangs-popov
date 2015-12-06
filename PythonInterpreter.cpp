#include "PythonInterpreter.h"
#include "InterpreterFactory.h"

#include <QCoreApplication>
#include <QDir>
#include <iostream>


void PythonInterpreter::initializeInterpeter()
{
    PyImport_AppendInittab("Actor", createActorModuleWrapper);
    Py_Initialize();
    m_interpreters[PyThreadState_Get()] = this;
    PyRun_SimpleString("from Actor import *\n");
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
    PyRun_SimpleString(utf8_program.constData());
}

int PythonInterpreter::trace(PyObject*, PyFrameObject*,
                             int what, PyObject *arg)
{
    PythonInterpreter* _this = m_interpreters[PyThreadState_Get()];
    if (PyTrace_EXCEPTION == what)
    {
        PyObject* exception = PyTuple_GetItem(arg, 1);
        PyObject* message = PyObject_Repr(exception);
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

PyObject* PythonInterpreter::createActorModuleWrapper()
{
    PyObject* moduleObject = PyModule_Create(&module);
    PyObject* moduleDict = PyModule_GetDict(moduleObject);
    QMapIterator<QString, QString> iterator(m_variables);
    while (iterator.hasNext())
    {
        iterator.next();
        PyObject* Variabe = PyUnicode_FromString(iterator.value().toUtf8().toStdString().c_str());
        Py_INCREF(Variabe);
        PyDict_SetItemString(moduleDict, iterator.key().toUtf8().toStdString().c_str() , Variabe);
    }
    return moduleObject;
}

PyObject* PythonInterpreter::printToCell(PyObject* , PyObject* args)
{
    QString text = "";
    PythonInterpreter* _this = m_interpreters[PyThreadState_Get()];
    if (PyTuple_Size(args) < 1)
    {
        PyErr_BadArgument();
        return NULL;
    }

    for (int index = 0; index < PyTuple_Size(args); ++ index)
    {
        PyObject* arg = PyTuple_GetItem(args, index);
        if (PyUnicode_Check(arg))
        {
            PyObject* string_bytes = PyUnicode_AsEncodedString(arg, "ASCII", "strict");
            if (string_bytes != NULL)
            {
                text = text + " " + QString(strdup(PyBytes_AsString(string_bytes)));
                Py_DECREF(string_bytes);
            }
            else
            {
                PyErr_BadArgument();
                return NULL;
            }
        }
        else if(PyLong_Check(arg))
        {
            text = text + " " + QString::number(PyLong_AsLong(arg));
        }
        else if(PyFloat_Check(arg))
        {
            text = text + " " + QString::number(PyFloat_AsDouble(arg));
        }
        else
        {
            PyErr_BadArgument();
            return NULL;
        }
    }
    _this->m_actor->printToCell(text);
    Py_INCREF(Py_None);
    return Py_None;
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
    m_variables.insert(name, value);
}


QMap<PyThreadState*, PythonInterpreter*> PythonInterpreter::m_interpreters;
QMap<QString, QString> PythonInterpreter::m_variables;


PyMethodDef PythonInterpreter::methods[] = {
    {"print", printToCell, METH_VARARGS, "Print output of programm"},
    {NULL, NULL, 0, NULL}
};

PyModuleDef PythonInterpreter::module = {
    PyModuleDef_HEAD_INIT,
    "Actor",
    "Control python programm",
    -1, methods,
    NULL, NULL, NULL
};

REGISTER_INTERPRETER(PythonInterpreter)
