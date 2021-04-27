QT += core gui widgets

CONFIG += debug_and_release debug_and_release_target
CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    logger.cpp \
    main.cpp \
    dialog.cpp

HEADERS += \
    dialog.h \
    logger.h

FORMS += \
    dialog.ui

RC_ICONS = icon.ico

VERSION = 1.1
QMAKE_TARGET_PRODUCT = $${TARGET}
QMAKE_TARGET_DESCRIPTION = $${TARGET}

