#ifndef ABSTRACTTASK_H
#define ABSTRACTTASK_H

#include <QObject>

class AbstractTask : public QObject
{
    Q_OBJECT
public:
    explicit AbstractTask(QObject *parent = nullptr);

    const QString &taskName() const;
    void setTaskName(const QString &newTaskName);

    const QString &taskType() const;
    void setTaskType(const QString &newTaskType);
    void startRun();

signals:
    void printLog(QString info);
protected:
    QString m_taskName;
    QString m_taskType;
    bool canRun();
    virtual void runTask();

};

#endif // ABSTRACTTASK_H
