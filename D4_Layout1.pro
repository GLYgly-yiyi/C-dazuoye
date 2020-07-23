QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets serialport sql

SOURCES += \
    layoutDemo.cpp \
    main.cpp \
    mainwindow.cpp \
    mytcpsocket.cpp \
    qwidgetdemo.cpp \
    qwidgetdraw.cpp \
    qwidgetserialrx.cpp \
    qwidgetserialtx.cpp

HEADERS += \
    layoutDemo.h \
    mainwindow.h \
    mytcpsocket.h \
    qwidgetdemo.h \
    qwidgetdraw.h \
    qwidgetserialrx.h \
    qwidgetserialtx.h

FORMS += \
    mainwindow.ui
