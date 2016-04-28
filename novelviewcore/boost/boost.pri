INCLUDEPATH += $$PWD
HEADERS += $$PWD/PartBoost.hpp

DEFINES += BOOST_HAS_TR1
DEFINES += BOOST_SP_USE_STD_ATOMIC
DEFINES += BOOST_ALL_NO_LIB
DEFINES += BOOST_FILESYSTEM_DYN_LINK

linux-g++*{
QMAKE_CXXFLAGS+=-Wno-ignored-qualifiers
QMAKE_CXXFLAGS+=-Wno-deprecated-declarations
}

win32-g++*{
QMAKE_CXXFLAGS+=-Wno-ignored-qualifiers
QMAKE_CXXFLAGS+=-Wno-deprecated-declarations
}

win32:{
#boost filesystem
LIBS += -lAdvapi32
}

