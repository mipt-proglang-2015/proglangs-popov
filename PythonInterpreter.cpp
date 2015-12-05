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
    if (_this->isTerminating())
    {
        PyErr_SetInterrupt();
    }
    return 0;
}

PyObject* PythonInterpreter::createActorModuleWrapper()
{
    static PyMethodDef methods[] = {
        {"Print", printToCell, METH_VARARGS, "Print output of programm"},
        {NULL, NULL, 0, NULL}
    };

    static PyModuleDef module = {
        PyModuleDef_HEAD_INIT,
        "Actor",
        "Control python programm",
        -1, methods,
        NULL, NULL, NULL
    };

    PyObject* moduleObject = PyModule_Create(&module);
    return moduleObject;
}

PyObject* PythonInterpreter::printToCell(PyObject* , PyObject* args)
{
    QString text;
    PythonInterpreter * _this = m_interpreters[PyThreadState_Get()];
    char* outString;
    int statusString = PyArg_ParseTuple(args, "s", &outString);
    if (!statusString)
    {
        int outInt;
        int statusInt = PyArg_ParseTuple(args, "i", &outInt);
        if (!statusInt)
        {
            PyErr_BadArgument();
            return NULL;
        }
        else
        {
            text = QString::number(outInt);
        }
    }
    else
    {
        text = QString(outString);
    }
    _this->m_actor->printToCell(text);
    Py_INCREF(Py_None);
    return Py_None;
}

QMap<PyThreadState*, PythonInterpreter*> PythonInterpreter::m_interpreters;

REGISTER_INTERPRETER(PythonInterpreter)
