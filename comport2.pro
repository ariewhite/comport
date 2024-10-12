QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    console.cpp \
    displaywindow.cpp \
    main.cpp \
    mainwindow.cpp \
    serialportreader.cpp \
    settingsdialog.cpp

HEADERS += \
    console.h \
    displaywindow.h \
    mainwindow.h \
    serialportreader.h \
    settingsdialog.h

FORMS += \
    console.ui \
    displaywindow.ui \
    mainwindow.ui \
    settingsdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    terminal.qrc
