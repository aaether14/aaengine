#-------------------------------------------------
#
# Project created by QtCreator 2016-01-29T16:11:49
#
#-------------------------------------------------

QT += core gui opengl qml



greaterThan(QT_MAJOR_VERSION, 4): QT += widgets



TARGET = AaetherEngine
TEMPLATE = app



SOURCES += main.cpp\
        controller.cpp \
    glcontroller.cpp \
    console/console.cpp \
    script_module/scriptengine.cpp \
    console/logger.cpp \
    fbx_manager/fbxmanager.cpp \
    fbx_manager/meshentry.cpp \
    fbx_manager/mesh.cpp \
    fps.cpp


HEADERS  += controller.hpp \
    glcontroller.hpp \
    console/console.hpp \
    script_module/scriptengine.hpp \
    console/logger.hpp \
    fbx_manager/fbxmanager.hpp \
    fbx_manager/meshentry.hpp \
    fbx_manager/mesh.hpp \
    fps.hpp




FORMS    += controller.ui \
    console.ui


CONFIG += c++11



RESOURCES += \
    resources.qrc


LIBS += -lfbxsdk

DISTFILES +=











