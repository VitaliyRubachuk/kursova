QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    adminwindow.cpp \
    databasemanager.cpp \
    main.cpp \
    mainwindow.cpp \
    managerwindow.cpp \
    usercard.cpp \
    userwindow.cpp

HEADERS += \
    adminwindow.h \
    databasemanager.h \
    mainwindow.h \
    managerwindow.h \
    usercardmanager.h \
    userwindowmanager.h

FORMS +=

QT += sql

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
