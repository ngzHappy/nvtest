CONFIG += c++14
QT     += widgets
QT     += network
QT     += core

!win32-msvc*{
QMAKE_CFLAGS+=-std=c99
QMAKE_CFLAGS+=-Wno-old-style-declaration
QMAKE_CFLAGS+=-Wno-unused-parameter
QMAKE_CFLAGS+=-Wno-unused-variable
}

CONFIG(debug,debug|release){
TARGET = novelviewcored
}else{
TARGET = novelviewcore
}

TEMPLATE = lib

DEFINES += NOVELVIEWCORE_LIBRARY
DEFINES += QUAZIP_BUILD
DEFINES += LUA_BUILD_AS_DLL

win32{
}else{
DEFINES += LUA_USE_LINUX
}

SOURCES += Novelviewcore.cpp

HEADERS += $$PWD/Novelviewcore.hpp
HEADERS += $$PWD/private/core_pre_build.h
HEADERS += $$PWD/private/msvc_core_pre_build.h
HEADERS += $$PWD/novelviewcore_global.hpp

include( $$PWD/gumbo/gumbo.pri )
include( $$PWD/core_utility.pri )
include( $$PWD/quazip/quazip.pri )
include( $$PWD/quazip/zlib.pri )
include( $$PWD/lua/lua.pri )
include( $$PWD/boost/boost.pri )
DEFINES += BOOST_FILESYSTEM_SOURCE
DEFINES += BOOST_SYSTEM_SOURCE
SOURCES += $$PWD/boost/libs/boost_codecvt_error_category.cpp
SOURCES += $$PWD/boost/libs/boost_error_code.cpp
SOURCES += $$PWD/boost/libs/boost_operations.cpp
SOURCES += $$PWD/boost/libs/boost_path.cpp
SOURCES += $$PWD/boost/libs/boost_path_traits.cpp
SOURCES += $$PWD/boost/libs/boost_portability.cpp
SOURCES += $$PWD/boost/libs/boost_unique_path.cpp
SOURCES += $$PWD/boost/libs/boost_utf8_codecvt_facet.cpp
SOURCES += $$PWD/boost/libs/boost_windows_file_codecvt.cpp

CONFIG += precompile_header
win32-msvc*{
PRECOMPILED_HEADER  += $$PWD/private/msvc_core_pre_build.h
}else{
PRECOMPILED_HEADER  += $$PWD/private/core_pre_build.h
}

!win32 {
    QMAKE_LFLAGS += -Wl,-rpath .
}
DESTDIR = $$OUTPWD

