QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/main.cpp \
    src/app/appcontroller.cpp \
    src/app/appsettings.cpp \
    src/app/appinternalstorage.cpp \
    src/console/consoleapplication.cpp \
    src/conversion/librenetlistparser.cpp \
    src/conversion/librenetlistupdater.cpp \
    src/conversion/spicenetlistproducer.cpp \
    src/conversion/data/conversionparams.cpp \
    src/conversion/data/conversiondata.cpp \
    src/conversion/output/componentprinter.cpp \
    src/ui/directorydialog.cpp \
    src/ui/mainwindow.cpp \
    src/ui/overflowinglabel.cpp \
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
    src/utils/uuidgenerator.cpp \
    src/utils/attributeutils.cpp \
    src/utils/characterutils.cpp

HEADERS += \
    src/main.h \
    src/app/appcontroller.h \
    src/app/appsettings.h \
    src/app/appinternalstorage.h \
    src/console/consoleapplication.h \
    src/conversion/librenetlistparser.h \
    src/conversion/librenetlistupdater.h \
    src/conversion/spicenetlistproducer.h \
    src/conversion/data/conversionparams.h \
    src/conversion/data/conversiondata.h \
    src/conversion/output/componentprinter.h \
    src/ui/directorydialog.h \
    src/ui/mainwindow.h \
    src/ui/overflowinglabel.h \
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
    src/utils/regexutils.h \
    src/utils/uuidgenerator.h \
    src/utils/attributeutils.h \
    src/utils/characterutils.h

FORMS += \
    ui/directorydialog.ui \
    ui/mainwindow.ui

RC_ICONS = resources/img/logo_small.ico

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    README.md

RESOURCES += \
    resources/resources.qrc
