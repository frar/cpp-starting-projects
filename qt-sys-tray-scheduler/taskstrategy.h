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
    int dayOfWeek;
    QTime time;
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

    typedef enum
    {
        FIXED,
        DAYTIME,
    } PeriodicityType;

    /**
     * \brief Function to update execution time using fixed interval periodicity
     */
    void updateExecutionTimeThroughFixedIntervalPeriodicity(){
        mNextExecutionTime = mNextExecutionTime.addYears(mFixedIntervalPeriodicity.year);
        mNextExecutionTime = mNextExecutionTime.addMonths(mFixedIntervalPeriodicity.month);
        mNextExecutionTime = mNextExecutionTime.addDays(mFixedIntervalPeriodicity.day);
        mNextExecutionTime = mNextExecutionTime.addSecs(mFixedIntervalPeriodicity.hour*60*60);
        mNextExecutionTime = mNextExecutionTime.addSecs(mFixedIntervalPeriodicity.minutes*60);
        mNextExecutionTime = mNextExecutionTime.addSecs(mFixedIntervalPeriodicity.secs);
    }

    /**
     * \brief Function to update execution time using daytime periodicity
     */
    void updateExecutionTimeThroughDayTimeIntervalPeriodicity(){
        // Look for the next dayname
        QDateTime todayDateTime =QDateTime::currentDateTime();
        QDateTime startingDateTime =todayDateTime;

        // Time must be the same in mDayNamePeriodicity while data must be found
        mNextExecutionTime.setTime(mDayNamePeriodicity.time);


        // Find next date with same day of week
        while(startingDateTime.date().dayOfWeek() != mDayNamePeriodicity.dayOfWeek)
            startingDateTime.addDays(1);

        // if today is the found date a check on the time is required
        if(todayDateTime.date() == startingDateTime.date())
        {
            if(startingDateTime.time() > mDayNamePeriodicity.time) // if time has already passed, the next day will be
                startingDateTime.setDate(startingDateTime.date().addDays(7));
        }

        // Set found date
        mNextExecutionTime.setDate(startingDateTime.date());
        // std::cout << "Next scheduled time" << mNextExecutionTime.toString().toStdString() << std::endl;
    }

    /**
     * brief Function to add periodicity of the task based on fixed intervals of time
     * \param year year periodicity
     * \param month month periodicity
     * \param day day periodicity
     * \param hour hour periodicity
     * \param minute minute periodicity
     * \param sec sec periodicity
     */
    void setFixedIntervalPeriodicity(const FixedIntervalPeriodicity &periodicity)
    {
        mFixedIntervalPeriodicity = periodicity;
        mNextExecutionTime = QDateTime::currentDateTime();
        updateExecutionTimeThroughFixedIntervalPeriodicity();
        mType = FIXED;
     }

    /**
     * brief Function to add periodicity of the task based on dayName (e.g. each monday at hour)
     * \param dayName dayName when to repeat the task
     * \param hour hour of esecution
     * \param minute minute of execution
     * \param sec sec of execution
     */
    void setDayNamePeriodicity(const DayNamePeriodicity &dayNamePeriodicity)
    {
        mDayNamePeriodicity = dayNamePeriodicity;
        updateExecutionTimeThroughDayTimeIntervalPeriodicity();
        mType = DAYTIME;
    }

    /**
     * \brief Function to check if time towards next execution has expired
     * \return true if time has expired, false otherwise
    */
    bool timerHasExpired(){
        QDateTime currentDateTime = QDateTime::currentDateTime();
        if(currentDateTime > mNextExecutionTime){
            if(mType == FIXED)
                updateExecutionTimeThroughFixedIntervalPeriodicity();
            else
                updateExecutionTimeThroughDayTimeIntervalPeriodicity();
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
    FixedIntervalPeriodicity mFixedIntervalPeriodicity;

    /**
     * \brief Vector to store periodicity of type DayName
     */
    DayNamePeriodicity mDayNamePeriodicity;

    /**
     * \brief Next execution time
     */
    QDateTime mNextExecutionTime;

    /**
     * \brief Variable to distinguish type of task
    */
    std::string mTaskName = "0";

    /**
     * \brief Variable that stores periodicity type (FIXED or DAYTIME)
    */
    PeriodicityType mType;
};

#endif // ITASK_H
