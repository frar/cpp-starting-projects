/***************************************|
**                                      |
** Copyright (C) 2018 Francesco Argese  |
** License: BSD                         |
**                                      |
****************************************/

#include "window.h"

#ifndef QT_NO_SYSTEMTRAYICON

// Qt headers
#include <QAction>
#include <QCoreApplication>
#include <QCloseEvent>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QMenu>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QTimer>

// C++ standard headers
#include <iostream>

// Project headers
#include <schedulertimer.h>
#include <task_t1.h>
#include <task_t2.h>

Window::Window()
{
    // Create GUI widgets
    createMessageGroupBox();
    createActions();
    createTrayIcon();

    // Connect signals to custom slots
    connect(setMessageButton, &QAbstractButton::clicked, this, &Window::setMessage);
    connect(trayIcon, &QSystemTrayIcon::messageClicked, this, &Window::messageClicked);

    // Add widgets to layout and add icon
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(t1GroupBox);
    setLayout(mainLayout);
    setIcon();

    // Show traiIcon
    trayIcon->show();

    // Add window title and resive
    setWindowTitle(tr("Generic Task Scheduler"));
    resize(400, 300);

    // Define task T1
    t1 = new Task_T1("Default message.");
    FixedIntervalPeriodicity periodicity_t1 = {0, 0, 0, 0, 0, 10};
    t1->setFixedIntervalPeriodicity(periodicity_t1);

    // Define task T2
    Task_T2 *t2 = new Task_T2();
    FixedIntervalPeriodicity periodicity_t2 = {0, 0, 0, 0, 0, 30};
    t2->setFixedIntervalPeriodicity(periodicity_t2);

    // Define task T1 with dayname periodicity (not required by base requirements, so commented out)
    /*Task_T1 *t1_dayname = new Task_T1("t1 dayname periodicity");
    DayNamePeriodicity periodicity_t3 = {6, QTime(13, 00, 0)};
    t1_dayname->setDayNamePeriodicity(periodicity_t3);*/

    // Run Scheduler Timer
    mSchedulerTimer = new SchedulerTimer;
    mSchedulerTimer->addTask(t1);
    mSchedulerTimer->addTask(t2);
    // mSchedulerTimer->addTask((t1_dayname));

    // Set timeout to call scheduler periodically
    connect(mSchedulerTimer, SIGNAL(timeout()), mSchedulerTimer, SLOT(executeNextTask()));

    // start the timer object by first dereferencing that object first
    mSchedulerTimer->start(1000);

}

Window::~Window()
{
    // Free ,memory dinamically allocated
    if(mSchedulerTimer != NULL)
    {
        delete mSchedulerTimer;
    }
}

void Window::setVisible(bool visible)
{
    // Set visible actions to handle the window
    minimizeAction->setEnabled(visible);
    maximizeAction->setEnabled(!isMaximized());
    restoreAction->setEnabled(isMaximized() || !visible);
    QDialog::setVisible(visible);
}

void Window::closeEvent(QCloseEvent *event)
{
#ifdef Q_OS_OSX
    if (!event->spontaneous() || !isVisible()) {
        return;
    }
#endif
    // Show message when closing the window (it is only hidden)
    if (trayIcon->isVisible()) {
        QMessageBox::information(this, tr("Systray"),
                                 tr("The program will keep running in the "
                                    "system tray. To terminate the program, "
                                    "choose <b>Quit</b> in the context menu "
                                    "of the system tray entry."));
        hide();
        event->ignore();
    }
}

void Window::setIcon()
{
    // Load and set icon
    QIcon icon = QIcon(":/images/icon.png");
    trayIcon->setIcon(icon);
    setWindowIcon(icon);

    trayIcon->setToolTip("Icon");
}

void Window::setMessage()
{
    // QSystemTrayIcon::MessageIcon msgIcon = QSystemTrayIcon::MessageIcon();
    trayIcon->showMessage("Message text updated", bodyEdit->toPlainText(), QSystemTrayIcon::Information, 1000);

    // Update message to be displayed
    t1->setMessage(bodyEdit->toPlainText().toStdString());
}

void Window::messageClicked()
{
    // Notify the update of the text for t1 that will
    QMessageBox::information(0, tr("Systray"),
                             tr("Sorry, I already gave what help I could.\n"
                                "Maybe you should try asking a human?"));
}

void Window::createMessageGroupBox()
{
    // Create wuidgets
    t1GroupBox = new QGroupBox(tr("T1 task configuration"));
    bodyLabel = new QLabel(tr("Text:"));
    bodyEdit = new QTextEdit;
    bodyEdit->setPlainText(tr("Test message"));
    setMessageButton = new QPushButton(tr("Set Message"));
    setMessageButton->setDefault(true);

    // Add widgets to layout
    QGridLayout *messageLayout = new QGridLayout;
    messageLayout->addWidget(bodyLabel, 0, 0);
    messageLayout->addWidget(bodyEdit, 1, 1, 1, 4);
    messageLayout->addWidget(setMessageButton, 4, 4);
    messageLayout->setColumnStretch(3, 1);
    messageLayout->setRowStretch(3, 1);
    t1GroupBox->setLayout(messageLayout);
}

void Window::createActions()
{
    // Create actions to handle window
    minimizeAction = new QAction(tr("Mi&nimize"), this);
    connect(minimizeAction, &QAction::triggered, this, &QWidget::hide);
    maximizeAction = new QAction(tr("Ma&ximize"), this);
    connect(maximizeAction, &QAction::triggered, this, &QWidget::showMaximized);
    restoreAction = new QAction(tr("&Restore"), this);
    connect(restoreAction, &QAction::triggered, this, &QWidget::showNormal);
    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);
}

void Window::createTrayIcon()
{
    // Create menù to be displayed on systray
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(minimizeAction);
    trayIconMenu->addAction(maximizeAction);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    // Add menù
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);
}

#endif
