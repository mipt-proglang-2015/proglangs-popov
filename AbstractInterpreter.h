#ifndef ABSTRACT_INTERPRETER_H
#define ABSTRACT_INTERPRETER_H

#include <QString>
#include <QMutex>
#include <QMap>
#include "Actor.h"


class AbstractInterpreter : public QObject
{
    Q_OBJECT

public:
    void setActor(Actor * actor);
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
    Actor* m_actor;
private:
    bool m_stopFlag;
    mutable QMutex m_stopMutex;

Q_SIGNALS:
    void logMessage(const QString& message);

public Q_SLOTS:
    void run(const QString& program);
};

#endif // ABSTRACT_INTERPRETER_H

