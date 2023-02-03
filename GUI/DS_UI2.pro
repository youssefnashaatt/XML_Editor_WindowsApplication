QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Helper_Functions.cpp \
    HuffmanTree.cpp \
    XML_Minifying.cpp \
    XML_Validation.cpp \
    XML_fileHandling.cpp \
    bitstring.cpp \
    compression.cpp \
    finddialog.cpp \
    graph.cpp \
    graphvizdialog.cpp \
    json.cpp \
    main.cpp \
    mainwindow.cpp \
    prettify.cpp \
    tree.cpp \
    users_analysis.cpp

HEADERS += \
    Helper_Functions.h \
    HuffmanTree.h \
    XML_Minifying.h \
    XML_Validation.h \
    XML_fileHandling.h \
    bitstring.h \
    compression.h \
    finddialog.h \
    graph.h \
    graphvizdialog.h \
    json.h \
    mainwindow.h \
    prettify.h \
    tree.h \
    users_analysis.h

FORMS += \
    finddialog.ui \
    graphvizdialog.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
