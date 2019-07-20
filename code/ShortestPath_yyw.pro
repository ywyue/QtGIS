#-------------------------------------------------
#
# Project created by QtCreator 2018-10-11T11:53:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ShortestPath_yyw
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
win32-g++ {
    LIBS += -lopengl32
}
win32-msvc*{
    LIBS += opengl32.lib
}

SOURCES += \
        main.cpp \
        mainwindow_yyw.cpp \
    CArc.cpp \
    CInfo.cpp \
    CInfoAAT.cpp \
    CInfoTIC.cpp \
    CNode.cpp \
    CMap.cpp \
    CFileManage.cpp \
    CGLFunction.cpp \
    CShortestPath.cpp \
    QueryDialog.cpp \
    ReadDialog.cpp

HEADERS += \
        mainwindow_yyw.h \
    CArc.h \
    CInfo.h \
    CInfoAAT.h \
    CInfoTIC.h \
    CNode.h \
    CMap.h \
    CFileManage.h \
    CGLFunction.h \
    CShortestPath.h \
    QueryDialog.h \
    ReadDialog.h

FORMS += \
        mainwindow_yyw.ui \
    querydialog.ui \
    readdialog.ui
