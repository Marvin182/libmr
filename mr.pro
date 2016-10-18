
QT       -= core

CONFIG   += c++11 staticlib

TARGET = mr

TEMPLATE = lib

include(gitversion.pri)
DEFINES += LIB_VERSION=\\\"$$GIT_VERSION\\\"

HEADERS += \
    src/common/assert.h \
    src/common/constants.h \
    src/common/random.h \
    src/common/Timer.h \
    src/common/vector.h \
    src/lib/pempek_assert.h \
    src/codejam.h \
    src/log.h \
    src/qt-app.h \
    src/qt-file.h \
    src/qt-string.h \
    src/Version.h

SOURCES += \
    src/common/assert.cpp \
    src/common/random.cpp \
    src/common/Timer.cpp \
    src/lib/pempek_assert.cpp \
    src/log.cpp \
    src/qt-app.cpp \
    src/qt-string.cpp \
    src/Version.cpp

