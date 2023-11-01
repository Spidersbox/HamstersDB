TARGET = HamstersDB
RC_ICONS = images/favicon.ico
QT += core gui
QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# add no pie so you can click on your app to run in linux
QMAKE_LFLAGS += -no-pie

#LIBS += -Wl,-Bstatic

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

OBJECTS_DIR = build
MOC_DIR = build
UI_DIR = build

SOURCES += src/main.cpp\
    src/mainwindow.cpp \
    src/dbman.cpp \
    src/searchform.cpp \
    src/callform.cpp \
    src/nameform.cpp

HEADERS  += src/mainwindow.h \
    src/dbman.h \
    src/searchform.h \
    src/callform.h \
    src/nameform.h

FORMS    += src/forms/mainwindow.ui \
    src/forms/SearchForm.ui \
    src/forms/NameForm.ui \
    src/forms/CallForm.ui

RESOURCES += src/hamstersdb.qrc
windows:RC_FILE = src/hamstersdb.rc

windows:LIBS += -static-libgcc 

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

