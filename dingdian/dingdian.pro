CONFIG += c++14

QT += core gui
QT += widgets
QT += concurrent
QT += network

TARGET = dingdian
TEMPLATE = app

include( $$PWD/../novelviewcore/core_utility.pri )
include( $$PWD/../novelviewcore/boost/boost.pri )
INCLUDEPATH += $$PWD/../novelviewcore/widget

CONFIG(debug,debug|release){
win32-msvc*{
CONFIG += console
}
LIBS+=-L$$OUTPWD -lnovelviewcored
}else{
LIBS+=-L$$OUTPWD -lnovelviewcore
}


HEADERS +=$$PWD/DingDianProcess.hpp
HEADERS +=$$PWD/ItemWidget.hpp
HEADERS +=$$PWD/private/ItemWidgetData.hpp
HEADERS +=$$PWD/private/ItemWidgetPrivateFunction.hpp
HEADERS +=$$PWD/private/DingDianModelData.hpp
HEADERS +=$$PWD/private/DingDianModelPrivateFunction.hpp
HEADERS +=$$PWD/DingDianModel.hpp
HEADERS +=$$PWD/CentralWidget.hpp
HEADERS +=$$PWD/private/CentralWidgetData.hpp
HEADERS +=$$PWD/private/CentralWidgetPrivateFunction.hpp
HEADERS +=$$PWD/AbstractItemWidget.hpp
HEADERS +=$$PWD/ListView.hpp
HEADERS +=$$PWD/private/ListViewData.hpp
HEADERS +=$$PWD/private/ListViewPrivateFunction.hpp
HEADERS +=$$PWD/private/DingDianProcessData.hpp
HEADERS +=$$PWD/private/DingDianProcessPrivateFunction.hpp
SOURCES +=$$PWD/DingDianProcess.cpp
SOURCES +=$$PWD/ItemWidget.cpp
SOURCES +=$$PWD/DingDianModel.cpp
SOURCES +=$$PWD/CentralWidget.cpp
SOURCES +=$$PWD/ListView.cpp

SOURCES += main.cpp\
        MainWindow.cpp

HEADERS  += $$PWD/MainWindow.hpp
HEADERS  += $$PWD/private/MainWindowData.hpp
HEADERS  += $$PWD/private/MainWindowPrivateFunction.hpp
HEADERS  += $$PWD/private/app_pre_build.h
HEADERS  += $$PWD/private/msvc_app_pre_build.h

CONFIG += precompile_header
win32-msvc*{
PRECOMPILED_HEADER  += $$PWD/private/msvc_app_pre_build.h
}else{
PRECOMPILED_HEADER  += $$PWD/private/app_pre_build.h
}

!win32 {
    QMAKE_LFLAGS += -Wl,-rpath .
}
DESTDIR = $$OUTPWD
