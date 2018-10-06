#ifndef ITASK_H
#define ITASK_H

// Standard C++ headers
#include <vector>
#include <string>
#include <iostream>

// Qt headers
#include <QDateTime>


/**
 * \brief Structure to define periodicity of type fixed interval
 */
struct FixedIntervalPeriodicity
{
    int year;
    int month;
    int day;
    int hour;
    int minutes;
    int secs;
};

/**
 * \brief Structure to define periodicity of type dayName
 */
struct DayNamePeriodicity
{
    std::string shortDayName;
    int hour;
    int minutes;
    int secs;
};

/**
 * \brief Interface that defines the skeleton of a task, including timing and periodicity.
 * Each new task must inherit from this class.
 *
 * It implements Strategy design pattern.
 */
class TaskStrategy
{
public:

    /**
     * \brief Default ctor
     */
    TaskStrategy(){
        // mNextExecutionTime = QDateTime::currentDateTime();
    }

    /**
     * brief Default dtor
     */
    virtual ~TaskStrategy(){}

    /**
     * \brief Function to update execution time using fixed interval periodicity
     */
    void updateExecutionTimeThroughFixedIntervalPeriodicity(){
        mNextExecutionTime = mNextExecutionTime.addYears(mFixedIntervalPeriodicity.at(0).year);
        mNextExecutionTime = mNextExecutionTime.addMonths(mFixedIntervalPeriodicity.at(0).month);
        mNextExecutionTime = mNextExecutionTime.addDays(mFixedIntervalPeriodicity.at(0).day);
        mNextExecutionTime = mNextExecutionTime.addSecs(mFixedIntervalPeriodicity.at(0).hour*60*60);
        mNextExecutionTime = mNextExecutionTime.addSecs(mFixedIntervalPeriodicity.at(0).minutes*60);
        mNextExecutionTime = mNextExecutionTime.addSecs(mFixedIntervalPeriodicity.at(0).secs);
    }

    /**
     * brief Funciton to add periodicity of the task based on fixed intervals of time
     * \param year year periodicity
     * \param month month periodicity
     * \param day day periodicity
     * \param hour hour periodicity
     * \param minute minute periodicity
     * \param sec sec periodicity
     */
    void addFixedIntervalPeriodicity(const FixedIntervalPeriodicity &periodicity)
    {
        mFixedIntervalPeriodicity.push_back(periodicity);
        mNextExecutionTime = QDateTime::currentDateTime();
        updateExecutionTimeThroughFixedIntervalPeriodicity();
     }

    /**
     * brief Function to add periodicity of the task based on dayName (e.g. each monday at hour)
     * \param dayName dayName when to repeat the task
     * \param hour hour of esecution
     * \param minute minute of execution
     * \param sec sec of execution
     */
    void addDayNamePeriodicity(const DayNamePeriodicity &dayNamePeriodicity)
    {
        mDayNamePeriodicity.push_back(dayNamePeriodicity);
    }

    /**
     * \brief Function to check if time towards next execution has expired
     * \return true if time has expired, false otherwise
    */
    bool timerHasExpired(){
        QDateTime currentDateTime = QDateTime::currentDateTime();
        if(currentDateTime > mNextExecutionTime){
            updateExecutionTimeThroughFixedIntervalPeriodicity();
            return true;
        }

        return false;
    }

    /**
     * \brief Function to print messages formatted for a specified task
     * \param message Message to be printed
    */
    void task_print(const std::string &message)
    {
        QDateTime currentDateTime = QDateTime::currentDateTime();
        /*std::string stringToBePrinted = std::string("Task ") + mTaskName + ": " + "\n\t" + currentDateTime.toString().toStdString() + std::string(" - ") + message.c_str() + "\n\n";
        qDebug(stringToBePrinted.c_str());*/
        qDebug("Task %s: \n\t%s - %s\n\n", mTaskName.c_str(), currentDateTime.toString().toStdString().c_str(), message.c_str());
    }

    /**
     * \brief Function to execute the task
     */
    virtual void execute() = 0 ;

protected:

    /**
     * \brief Vector to store periodicity of type fixed interval
     */
    std::vector<FixedIntervalPeriodicity> mFixedIntervalPeriodicity;

    /**
     * \brief Vector to store periodicity of type DayName
     */
    std::vector<DayNamePeriodicity> mDayNamePeriodicity;

    /**
     * \brief Next execution time
     */
    QDateTime mNextExecutionTime;

    /**
     * \brief Variable to distinguish type of task
    */
    std::string mTaskName = "0";
};

#endif // ITASK_H
