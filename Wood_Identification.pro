#-------------------------------------------------
#
# Project created by QtCreator 2019-06-26T14:11:17
#
#-------------------------------------------------

QT       += core gui

RC_ICONS = log.ico

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Wood_Identification
TEMPLATE = app


# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    qcvdisplay.cpp \
    algorithm/eigenvalue.cpp \
    adjust_dialog.cpp \
    algorithm/eigenvalue.cpp \
    algorithm/equalizehist.cpp \
    algorithm/split_rgb.cpp \
    algorithm/butterworth.cpp \
    process/process.cpp

HEADERS += \
        mainwindow.h \
    qcvdisplay.h \
    algorithm/butterworth.h \
    algorithm/equalizehist.h \
    algorithm/split_rgb.h \
    algorithm/eigenvalue.h \
    process/process.h \
    adjust_dialog.h

FORMS += \
        mainwindow.ui \
    adjust_dialog.ui

INCLUDEPATH += D:\opencv\build\include\opencv\
               D:\opencv\build\include\opencv2\
               D:\opencv\build\include

LIBS += D:\opencv\build\x64\vc14\lib\opencv_world401d.lib
LIBS += D:\opencv\build\x64\vc14\lib\opencv_world401.lib

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


