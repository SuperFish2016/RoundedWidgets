QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(iconfont/iconfonthelper.pri)

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    RoundedWindow.cpp \
    main.cpp \
    mainwindow.cpp \
    roundedwidget/roundedmenu.cpp \
    roundedmessagebox.cpp \
    roundedwidget/roundedwidget.cpp \
    tabwidget/tabbar.cpp \
    tabwidget/tabpagewidget.cpp \
    tabwidget/tabwidget.cpp \
    tabwidget/tabwindow.cpp \
    tabwidget/windowcontrolbuttons.cpp \
    toolbar.cpp

HEADERS += \
    RoundedWindow.h \
    mainwindow.h \
    roundedwidget/roundedmenu.h \
    roundedmessagebox.h \
    roundedwidget/roundedwidget.h \
    style.h \
    tabwidget/tabbar.h \
    tabwidget/tabbardrawhelper.h \
    tabwidget/tabpagewidget.h \
    tabwidget/tabwidget.h \
    tabwidget/tabwindow.h \
    tabwidget/windowcontrolbuttons.h \
    toolbar.h

FORMS += \
    mainwindow.ui
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
