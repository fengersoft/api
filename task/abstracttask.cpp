#include "abstracttask.h"

AbstractTask::AbstractTask(QObject *parent)
    : QObject{parent}
{


}

const QString &AbstractTask::taskName() const
{
    return m_taskName;
}

void AbstractTask::setTaskName(const QString &newTaskName)
{
    m_taskName = newTaskName;
}

const QString &AbstractTask::taskType() const
{
    return m_taskType;
}

void AbstractTask::setTaskType(const QString &newTaskType)
{
    m_taskType = newTaskType;
}

void AbstractTask::startRun()
{
    if (canRun())
    {
        runTask();
    }

}

bool AbstractTask::canRun()
{
    return true;
}

void AbstractTask::runTask()
{
    //在具体类实现

}
