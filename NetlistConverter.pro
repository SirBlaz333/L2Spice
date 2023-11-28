QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/main.cpp \
    src/app/appsettings.cpp \
    src/ui/mainwindow.cpp \
    src/ui/homedirectorydialog.cpp \
    src/file/filemanager.cpp \
    src/circuit/circuit.cpp \
    src/circuit/element/attribute.cpp \
    src/circuit/element/component.cpp \
    src/circuit/element/device.cpp \
    src/circuit/element/element.cpp \
    src/circuit/element/net.cpp \
    src/circuit/element/netclass.cpp \
    src/circuit/element/signal.cpp \
    src/circuit/element/variant.cpp \
    src/netlist/netlistparser.cpp \
    src/netlist/netlistproducer.cpp \
    src/netlist/netlisttemporarystorage.cpp \
    src/netlist/netlisttemporarystoragenode.cpp \
    src/netlist/netlistupdater.cpp \
    src/utils/uuidgenerator.cpp \
    src/utils/attributeutils.cpp \
    src/utils/characterutils.cpp

HEADERS += \
    src/main.h \
    src/app/appsettings.h \
    src/ui/mainwindow.h \
    src/ui/homedirectorydialog.h \
    src/file/filemanager.h \
    src/circuit/circuit.h \
    src/circuit/element/attribute.h \
    src/circuit/element/component.h \
    src/circuit/element/device.h \
    src/circuit/element/element.h \
    src/circuit/element/net.h \
    src/circuit/element/netclass.h \
    src/circuit/element/signal.h \
    src/circuit/element/variant.h \
    src/netlist/netlistparser.h \
    src/netlist/netlistproducer.h \
    src/netlist/netlisttemporarystorage.h \
    src/netlist/netlisttemporarystoragenode.h \
    src/netlist/netlistupdater.h \
    src/utils/uuidgenerator.h \
    src/utils/attributeutils.h \
    src/utils/characterutils.h

FORMS += \
    ui/mainwindow.ui \
    ui/homedirectorydialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    README.md

RESOURCES += \
    resources/resources.qrc
