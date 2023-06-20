QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    additivemathelements.cpp \
    illuminantplacechooser.cpp \
    main.cpp \
    mainwindow.cpp \
    movechooser.cpp \
    objectchanger.cpp \
    objecthangman.cpp \
    objects.cpp \
    placechooser.cpp \
    sizechooser.cpp \
    specialgraphicsview.cpp \
    usagefacade.cpp

HEADERS += \
    additivemathelements.hpp \
    config.hpp \
    illuminantplacechooser.hpp \
    mainwindow.h \
    movechooser.hpp \
    objectchanger.hpp \
    objecthangman.hpp \
    objects.hpp \
    placechooser.h \
    sizechooser.hpp \
    specialgraphicsview.hpp \
    usagefacade.hpp

FORMS += \
    illuminantplacechooser.ui \
    mainwindow.ui \
    movechooser.ui \
    objectchanger.ui \
    objecthangman.ui \
#    placecarсhooser.ui \
    placebedchooser.ui \
    placeboardchooser.ui \
    placechairchooser.ui \
#    placeroadсhooser.ui \
    placetablechooser.ui \
    placetorsherchooser.ui \
    placetvchooser.ui \
    sizechooser.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

SUBDIRS += \
    proj.pro

DISTFILES += \
    compare.py
