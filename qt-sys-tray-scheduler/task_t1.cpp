#include "task_t1.h"

// Qt headers
#include <QtDebug>

Task_T1::Task_T1(const std::string & message) : TaskStrategy()
{
    mTaskName = "1";
    mMessage = message;
}

void Task_T1::setMessage(const std::string &message)
{
    mMessage = message;
}

void Task_T1::execute()
{
    task_print(mMessage.c_str());
}
