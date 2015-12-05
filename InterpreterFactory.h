#ifndef INTERPRETERFACTORY_H
#define INTERPRETERFACTORY_H

#include "AbstractInterpreter.h"

class InterpreterFactory
{
public:
    static AbstractInterpreter* get();

private:
    static AbstractInterpreter* m_instance;
};

#define REGISTER_INTERPRETER(ClassName) \
    static ClassName interpreterInstance; \
    AbstractInterpreter* InterpreterFactory::m_instance = &interpreterInstance;

#endif // INTERPRETERFACTORY_H
