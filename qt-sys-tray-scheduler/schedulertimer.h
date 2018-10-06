#ifndef SCHEDULERTIMER_H
#define SCHEDULERTIMER_H

#include <QTimer>

#include "taskstrategy.h"

/**
 * \brief Class to schedule tasks, executing them in background at specified periodiciity
 */
class SchedulerTimer : public QTimer
{
    Q_OBJECT
public:

    /**
     * \brief Default ctor
     * It initialized the scheduler timer
     */
    explicit SchedulerTimer(QObject *parent = nullptr);

    /**
     * \brief Default dtor
     * It destroys existing objects before closing
    */
    ~SchedulerTimer();

    /**
     * \brief Function to add a task to the  scheduler
     * \param task Task to be executed
     */
    void addTask(TaskStrategy *newTask);

signals:

public slots:

    /**
     * brief Function to execute next task
     */
    void executeNextTask();
private:

    /**
     * \brief Vector containing tasks to be executed
     */
    std::vector<TaskStrategy *> mScheduledTasks;

};

#endif // SCHEDULERTIMER_H
