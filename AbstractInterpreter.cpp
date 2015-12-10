#include "AbstractInterpreter.h"

void AbstractInterpreter::reset()
{
    m_errorMessage.clear();
}

QString AbstractInterpreter::errorMessage() const
{
    return m_errorMessage;
}

AbstractInterpreter::AbstractInterpreter()
{
}

