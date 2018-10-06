/***************************************|
**                                      |
** Copyright (C) 2018 Francesco Argese  |
** License: BSD                         |
**                                      |
****************************************/

#ifndef WINDOW_H
#define WINDOW_H

#include <QSystemTrayIcon>

#ifndef QT_NO_SYSTEMTRAYICON

// Qt headers
#include <QDialog>
#include <QPointer>

// Project headers
#include <schedulertimer.h>
#include <task_t1.h>

// Forward declaration
QT_BEGIN_NAMESPACE
class QAction;
class QCheckBox;
class QComboBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QMenu;
class QPushButton;
class QSpinBox;
class QTextEdit;
QT_END_NAMESPACE



/**
 * \brief Class that defines the Qt gui interface for task scheduler
 * and that launches the timer for starting task scheduling
 *
 * For reference on sysTray see the following url or example systray among Qt official examples:
 *  http://doc.qt.io/archives/qt-4.8/qt-desktop-systray-example.html
 */
class Window : public QDialog
{
    Q_OBJECT

public:

    /**
     * \brief Default ctor: it defines the main interfaces and menù and start the task scheduler
    */
    Window();

    /**
     * \brief Default dtor
     */
    ~Window();

    /**
     * \brief Function to set thewindow visible
     */
    void setVisible(bool visible) override;

    /**
     * \brief Function to set icon
    */
    void setIcon();

protected:

    /**
     * \brief closeEvent inherited from base class
     * Called when windows is closed
    */
    void closeEvent(QCloseEvent *event) override;

private slots:

    /**
     * \brief Function (SLOT) to set message of thread of t1 called at button click
    */
    void setMessage();

    /**
     * \brief Slot called when message is clicked
    */
    void messageClicked();

private:

    // Functions to create GUI main widgets
    void createMessageGroupBox();
    void createActions();
    void createTrayIcon();

    // Widgets and buttons for main window
    QGroupBox *t1GroupBox;
    QLabel *bodyLabel;
    QTextEdit *bodyEdit;
    QPushButton *setMessageButton;

    // Actions to handle window resizing
    QAction *minimizeAction;
    QAction *maximizeAction;
    QAction *restoreAction;
    QAction *quitAction;

    // Widgets for trayIcon and trayIcon menu
    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;

    /**
     * \brief Pointer to SchedulerTimer, object to schedule tasks
    */
    QPointer<SchedulerTimer> mSchedulerTimer;

    /**
     * \brief Pointer to Task T1 (required to change message)
    */
    Task_T1 *t1;
};

#endif // QT_NO_SYSTEMTRAYICON

#endif
