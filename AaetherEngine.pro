#-------------------------------------------------
#
# Project created by QtCreator 2016-01-29T16:11:49
#
#-------------------------------------------------

QT       += core gui opengl qml



greaterThan(QT_MAJOR_VERSION, 4): QT += widgets



TARGET = AaetherEngine
TEMPLATE = app



SOURCES += main.cpp\
        controller.cpp \
    glcontroller.cpp \
    console.cpp \
    scriptengine.cpp


HEADERS  += controller.hpp \
    glcontroller.hpp \
    console.hpp \
    scriptengine.hpp




FORMS    += controller.ui \
    console.ui


CONFIG += c++11
