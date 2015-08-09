
QT       -= core

CONFIG   += c++11 staticlib

TARGET = mr

TEMPLATE = lib

include(gitversion.pri)
DEFINES += LIB_VERSION=\\\"$$GIT_VERSION\\\"

HEADERS += \
    include/mr/common \
    include/mr/timer \
    include/mr/version \
    src/assert.h \
    src/codejam.h \
    src/file-util.h \
    src/log.h \
    src/pempek_assert.h \
    src/qt-util.h \
    src/random.h \
    src/string-util.h \
    src/Timer.h \
    src/vector.h \
    src/Version.h

SOURCES += \
    src/assert.cpp \
    src/log.cpp \
    src/pempek_assert.cpp \
    src/qt-util.cpp \
    src/random.cpp \
    src/string-util.cpp \
    src/Timer.cpp \
    src/Version.cpp

