

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
    core/glcontroller.cpp \
    dialogs/console/console.cpp \
    script_module/scriptengine.cpp \
    dialogs/console/logger.cpp \
    fbx_manager/fbxmanager.cpp \
    fbx_manager/entry/meshentry.cpp \
    fbx_manager/mesh/mesh.cpp \
    core/fps.cpp \
    core/inputregister.cpp \
    core/main_controller.cpp \
    fbx_manager/material/material.cpp \
    dialogs/about/about.cpp \
    renderer/baserenderer.cpp \
    renderer/pipeline.cpp \
    renderer/fbxrenderer.cpp \
    assets/baseasset.cpp \
    assets/meshasset.cpp \
    assets/baseassetloader.cpp \
    assets/assetloader.cpp \
    utils/math.cpp \
    core/projectmanager.cpp \
    utils/json.cpp \
    script_module/gameobject.cpp \
    fbx_manager/mesh/mesh_material.cpp \
    fbx_manager/mesh/mesh_buffer_loader.cpp \
    fbx_manager/mesh/mesh_cached_draw.cpp \
    error/aerror.cpp \
    dialogs/mesh_import_dialog/meshimport.cpp \
    dialogs/base_dialog.cpp \
    fbx_manager/mesh/mesh_scene_normalize.cpp \
    fbx_manager/entry/mesh_entry_normals.cpp \
    fbx_manager/entry/mesh_entry_uvs.cpp \
    fbx_manager/entry/mesh_entry_tangent.cpp \
    fbx_manager/mesh_util.cpp \
    fbx_manager/mesh/mesh_accelerated_draw.cpp \
    fbx_manager/mesh/geometryloader.cpp



HEADERS  += \
    core/glcontroller.hpp \
    dialogs/console/console.hpp \
    script_module/scriptengine.hpp \
    dialogs/console/logger.hpp \
    fbx_manager/fbxmanager.hpp \
    fbx_manager/entry/meshentry.hpp \
    fbx_manager/mesh/mesh.hpp \
    core/fps.hpp \
    core/inputregister.hpp \
    core/main_controller.hpp \
    fbx_manager/material/material.hpp \
    dialogs/about/about.hpp \
    renderer/baserenderer.hpp \
    renderer/pipeline.hpp \
    renderer/fbxrenderer.hpp \
    assets/baseasset.hpp \
    assets/meshasset.hpp \
    assets/baseassetloader.hpp \
    assets/assetloader.hpp \
    utils/math.hpp \
    core/projectmanager.hpp \
    utils/json.hpp \
    script_module/gameobject.hpp \
    error/aerror.hpp \
    dialogs/mesh_import_dialog/meshimport.hpp \
    dialogs/base_dialog.hpp \
    fbx_manager/mesh/mesh_gpu_memory.h \
    fbx_manager/mesh_util.hpp \
    fbx_manager/mesh/geometryloader.hpp




FORMS    += core/controller.ui \
    dialogs/console/console.ui \
    dialogs/about/about.ui \
    dialogs/mesh_import_dialog/meshimport.ui




CONFIG += c++11




RESOURCES += \
    resources.qrc



LIBS += -lfbxsdk















