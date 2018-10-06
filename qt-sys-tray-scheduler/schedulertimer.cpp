/***************************************|
**                                      |
** Copyright (C) 2018 Francesco Argese  |
** License: BSD                         |
**                                      |
****************************************/

#include "schedulertimer.h"

// Standard C++ headers
#include <iostream>

// Qt headers
#include <QDateTime>

SchedulerTimer::SchedulerTimer(QObject *parent) : QTimer(parent)
{

}

SchedulerTimer::~SchedulerTimer()
{
    for(unsigned int i = 0; i < mScheduledTasks.size(); i++){
        delete mScheduledTasks.at(i);
    }
}

void SchedulerTimer::addTask(TaskStrategy *newTask){
    mScheduledTasks.push_back(newTask);
}

void SchedulerTimer::executeNextTask(){

    for(unsigned int i = 0; i < mScheduledTasks.size(); i++){
        TaskStrategy *task = mScheduledTasks.at(i);
        if(task->timerHasExpired())
            task->execute();
    }


}
