QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
LIBS += -lmysqlclient
# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dbmanagewindow.cpp \
    logindialog.cpp \
    main.cpp \
    mainwindow.cpp \
    registerdialog.cpp \
    libraryManage.cpp \
    utility.cpp \
    checkInfoDialog.cpp \
    borrowBookDialog.cpp \
    searchBookDialog.cpp \
    addItemDialog.cpp \
    addTitleDialog.cpp \
    deleteItemDialog.cpp \
    deleteTitleDialog.cpp \
    returnBookDialog.cpp \
    reserveBookDialog.cpp \
    unreserveBookDialog.cpp

HEADERS += \
    dbmanagewindow.h \
    logindialog.h \
    mainwindow.h \
    registerdialog.h \
    libraryManage.h \
    utility.h \
    checkInfoDialog.h \
    borrowBookDialog.h \
    searchBookDialog.h \
    addItemDialog.h \
    addTitleDialog.h \
    deleteTitleDialog.h \
    deleteItemDialog.h \
    returnBookDialog.h \
    reserveBookDialog.h \
    unreserveBookDialog.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
