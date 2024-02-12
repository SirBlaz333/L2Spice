QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/main.cpp \
    src/app/app_controller.cpp \
    src/app/app_internal_storage.cpp \
    src/app/app_settings.cpp \
    src/app/app_state.cpp \
    src/app/app_header.cpp \
    src/console/console_app.cpp \
    src/console/flag.cpp \
    src/conversion/data/conversion_params.cpp \
    src/conversion/libre_netlist_parser.cpp \
    src/conversion/libre_netlist_updater.cpp \
    src/conversion/output/spice_printer.cpp \
    src/conversion/spice_netlist_producer.cpp \
    src/file/file_manager.cpp \
    src/circuit/circuit.cpp \
    src/circuit/element/attribute.cpp \
    src/circuit/element/component.cpp \
    src/circuit/element/device.cpp \
    src/circuit/element/element.cpp \
    src/circuit/element/net.cpp \
    src/circuit/element/netclass.cpp \
    src/circuit/element/signal.cpp \
    src/circuit/element/variant.cpp \
    src/ui/mainwindow.cpp \
    src/ui/notification_manager.cpp \
    src/ui/overflowing_label.cpp \
    src/ui/preferences_tabs.cpp \
    src/utils/attribute_utils.cpp \
    src/utils/character_utils.cpp \
    src/utils/global_variables.cpp \
    src/utils/uuid_generator.cpp

HEADERS += \
    src/main.h \
    src/app/app_controller.h \
    src/app/app_internal_storage.h \
    src/app/app_settings.h \
    src/app/app_state.h \
    src/app/app_header.h \
    src/console/console_app.h \
    src/console/flag.h \
    src/conversion/data/conversion_params.h \
    src/conversion/libre_netlist_parser.h \
    src/conversion/libre_netlist_updater.h \
    src/conversion/output/spice_printer.h \
    src/conversion/spice_netlist_producer.h \
    src/file/file_manager.h \
    src/circuit/circuit.h \
    src/circuit/element/attribute.h \
    src/circuit/element/component.h \
    src/circuit/element/device.h \
    src/circuit/element/element.h \
    src/circuit/element/net.h \
    src/circuit/element/netclass.h \
    src/circuit/element/signal.h \
    src/circuit/element/variant.h \
    src/ui/mainwindow.h \
    src/ui/notification_manager.h \
    src/ui/overflowing_label.h \
    src/ui/preferences_tabs.h \
    src/utils/attribute_utils.h \
    src/utils/character_utils.h \
    src/utils/global_variables.h \
    src/utils/regex_utils.h \
    src/utils/uuid_generator.h

FORMS += \
    ui/mainwindow.ui \
    ui/preferences.ui

RC_ICONS = resources/img/logo_small.ico

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    README.md

RESOURCES += \
    resources/resources.qrc
