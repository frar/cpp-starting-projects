HEADERS       = window.h \
    schedulertimer.h \
    task_t1.h \
    taskstrategy.h \
    task_t2.h
SOURCES       = main.cpp \
                window.cpp \
    schedulertimer.cpp \
    task_t1.cpp \
    task_t2.cpp
RESOURCES     = systray.qrc

QT += widgets

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/desktop/systray
INSTALLS += target
