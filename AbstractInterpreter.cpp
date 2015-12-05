#include "AbstractInterpreter.h"

void AbstractInterpreter::setActor(Actor *actor)
{
    m_actor = actor;
}

void AbstractInterpreter::terminateEvaluation()
{
    m_stopMutex.lock();
    m_stopFlag = true;
    m_stopMutex.unlock();
}

void AbstractInterpreter::reset()
{
    m_stopMutex.lock();
    m_stopFlag = false;
    m_stopMutex.unlock();
    m_errorMessage.clear();    
}

QString AbstractInterpreter::errorMessage() const
{
    return m_errorMessage;
}

AbstractInterpreter::AbstractInterpreter()
    : m_stopFlag(false)
{
}

void AbstractInterpreter::run(const QString &program)
{
    reset();
    initializeInterpeter();
    evaluateProgram(program);
    if (!isTerminating() && errorMessage().length() > 0)
    {
        emit logMessage(errorMessage() + "\n");
    }
    finalizeInterpreter();
}


bool AbstractInterpreter::isTerminating() const
{
    m_stopMutex.lock();
    const bool result = m_stopFlag;
    m_stopMutex.unlock();
    return result;
}

