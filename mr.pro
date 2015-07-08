
QT       -= core

CONFIG   += c++11 staticlib

TARGET = mr

TEMPLATE = lib

include(gitversion.pri)
DEFINES += LIB_VERSION=\\\"$$GIT_VERSION\\\"

HEADERS += \
    include/mr/common.h \
    src/qt-util.h \
    src/assert.h \
    src/pempek_assert.h \
    src/string-util.h \
    src/codejam.h \
    src/random.h \
    src/vector.h \
    src/Timer.h \
    src/Version.h

SOURCES += \
    src/qt-util.cpp \
    src/assert.cpp \
    src/random.cpp \
    src/pempek_assert.cpp \
    src/string-util.cpp
    src/Timer.cpp \
    src/Version.cpp

