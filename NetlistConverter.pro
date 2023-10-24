QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/attribute.cpp \
    src/characterutils.cpp \
    src/circuit.cpp \
    src/component.cpp \
    src/device.cpp \
    src/element.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/net.cpp \
    src/netclass.cpp \
    src/netlistparser.cpp \
    src/signal.cpp \
    src/uuidgenerator.cpp \
    src/variant.cpp

HEADERS += \
    headers/attribute.h \
    headers/characterutils.h \
    headers/circuit.h \
    headers/component.h \
    headers/device.h \
    headers/element.h \
    headers/mainwindow.h \
    headers/net.h \
    headers/netclass.h \
    headers/netlistparser.h \
    headers/signal.h \
    headers/uuidgenerator.h \
    headers/variant.h

FORMS += \
    ui/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    README.md

RESOURCES += \
    resources/resources.qrc
