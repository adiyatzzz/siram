QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    formchecker.cpp \
    formjadwal.cpp \
    formkandang.cpp \
    formpakan.cpp \
    formpopulasi.cpp \
    formproduksi.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    formchecker.h \
    formjadwal.h \
    formkandang.h \
    formpakan.h \
    formpopulasi.h \
    formproduksi.h \
    mainwindow.h

FORMS += \
    formjadwal.ui \
    formkandang.ui \
    formpakan.ui \
    formpopulasi.ui \
    formproduksi.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
