#ifndef ABSTRACT_INTERPRETER_H
#define ABSTRACT_INTERPRETER_H

#include <QString>
#include <QMutex>
#include <QMap>
#include <QObject>


class AbstractInterpreter : public QObject
{
    Q_OBJECT

public:
    virtual void initializeInterpeter() = 0;
    virtual void finalizeInterpreter() = 0;
    virtual void evaluateProgram(const QString& program) = 0;
    void terminateEvaluation();
    bool isTerminating() const;
    void reset();
    QString errorMessage() const;
protected:
    explicit AbstractInterpreter();
    QString m_errorMessage;

Q_SIGNALS:
    void logMessage(const QString& message);
    void printToFocusedCell(const QString& text);

public Q_SLOTS:
    virtual void run(const QString& program) = 0;
    virtual void addVariable(const QString& name, const QString& value) = 0;
};

#endif // ABSTRACT_INTERPRETER_H

