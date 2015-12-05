#include "InterpreterFactory.h"

AbstractInterpreter* InterpreterFactory::get()
{
    Q_ASSERT(m_instance);
    return m_instance;
}
