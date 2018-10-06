/***************************************|
**                                      |
** Copyright (C) 2018 Francesco Argese  |
** License: BSD                         |
**                                      |
****************************************/

#ifndef TASK_T2_H
#define TASK_T2_H

// Project headers
#include <taskstrategy.h>

// Qt headers
#include <QString>

/**
 * \brief Implementation of the type of task Task_T2
 */
class Task_T2 : public TaskStrategy
{
public:
    /**
     * \brief Default ctor
     */
    Task_T2();

    /**
     * \brief Function to execute task
    */
    virtual void execute();

private:

    /**
     * \brief Functiono to check if a filepath exists
     * \param path path to be checked
     * \return True if the file is found, false otherwise
    */
    bool fileExists(QString path);

};

#endif // TASK_T2_H
