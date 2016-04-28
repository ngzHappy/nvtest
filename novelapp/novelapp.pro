CONFIG += c++14

QT += core gui
QT += widgets

TARGET = novelview
TEMPLATE = app

include( $$PWD/../novelviewcore/core_utility.pri )
include( $$PWD/../novelviewcore/boost/boost.pri )

CONFIG(debug,debug|release){
LIBS+=-L$$OUTPWD -lnovelviewcored
}else{
LIBS+=-L$$OUTPWD -lnovelviewcore
}

SOURCES += main.cpp\
        MainWindow.cpp

HEADERS  += $$PWD/MainWindow.hpp
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


