/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

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
