
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
    src/codejam.h \
    src/constants.h \
    src/random.h \
    src/vector.h \
    src/assert.h \
    src/log.h \
    src/pempek_assert.h \
    src/qt-app.h \
    src/qt-util.h \
    src/qt-string.h \
    src/Timer.h \
    src/Version.h

SOURCES += \
    src/random.cpp \
    src/assert.cpp \
    src/log.cpp \
    src/pempek_assert.cpp \
    src/qt-app.cpp \
    src/qt-string.cpp \
    src/Timer.cpp \
    src/Version.cpp

