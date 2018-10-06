/***************************************|
**                                      |
** Copyright (C) 2018 Francesco Argese  |
** License: BSD                         |
**                                      |
****************************************/

#ifndef TASK_T1_H
#define TASK_T1_H

// Project headers
#include <taskstrategy.h>

/**
 * \brief Implementation of the type of task Task_T1, that write a text during debug run
 */
class Task_T1 : public TaskStrategy
{
public:
    /**
     * \brief Default ctor
     * \param Message to be printed
     */
    Task_T1(const std::string & message);

    /**
     * \brief Funciton to set message
     * \param message Message to be set
     */
    void setMessage(const std::string &message);

    /**
     * \brief Function to execute task
    */
    virtual void execute();

private:
    /**
     * \brief Message to be printed
     */
    std::string mMessage;
};

#endif // TASK_T1_H
