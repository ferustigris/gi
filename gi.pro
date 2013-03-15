# -------------------------------------------------
# Project created by QtCreator 2009-11-19T10:26:33
# -------------------------------------------------
QT += network \
    webkit
TARGET = gi
TEMPLATE = app
INCLUDEPATH += sources/ \
    sources/widgets
SOURCES += sources/main.cpp \
    sources/mainwindow.cpp \
    sources/errors.cpp \
    sources/widget.cpp \
    sources/widgets/label.cpp \
    sources/widgets/labelf.cpp \
    sources/widgets/labeli.cpp \
    sources/widgets/graphbody.cpp \
    sources/widgets/graph.cpp \
    sources/log.cpp \
    sources/widgets/list.cpp \
    sources/widgets/enterfloat.cpp \
    sources/widgets/led.cpp \
    sources/widgets/dial.cpp \
    sources/widgets/dock.cpp \
    sources/widgets/lcd.cpp \
    sources/widgets/enterint.cpp
HEADERS += sources/mainwindow.h \
    sources/errors.h \
    sources/widget.h \
    sources/widgets/label.h \
    sources/widgets/labelf.h \
    sources/widgets/labeli.h \
    sources/widgets/graphbody.h \
    sources/widgets/graph.h \
    sources/log.h \
    sources/widgets/list.h \
    sources/widgets/enterfloat.h \
    sources/widgets/led.h \
    sources/widgets/dial.h \
    sources/widgets/dock.h \
    sources/widgets/lcd.h \
    sources/widgets/enterint.h
FORMS += sources/widgets/graph.ui \
    sources/log.ui
RESOURCES += share/res.qrc
