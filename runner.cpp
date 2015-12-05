#include "runner.h"


Runner::Runner(AbstractInterpreter * interpreter,
               const QPlainTextEdit * editor)
    : QThread()
    , m_interpreter(interpreter)
    , m_editor(editor)
{

}

void Runner::stopAndWaitForFinished()
{
	stop();
	wait();
}

void Runner::stop()
{
    m_interpreter->terminateEvaluation();
}

void Runner::run()
{
    m_interpreter->reset();
    const QString programText = m_editor->toPlainText();
    m_interpreter->initializeInterpeter();
    m_interpreter->evaluateProgram(programText);
    if (!m_interpreter->isTerminating() && m_interpreter->errorMessage().length() > 0) {
        Q_EMIT logMessage(m_interpreter->errorMessage() + "\n");
    }
    m_interpreter->finalizeInterpreter();
}

