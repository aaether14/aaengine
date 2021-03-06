

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
    core/gl/glcontroller.cpp \
    dialogs/console/console.cpp \
    script_module/scriptengine.cpp \
    dialogs/console/logger.cpp \
    fbx_manager/fbxmanager.cpp \
    fbx_manager/entry/meshentry.cpp \
    fbx_manager/mesh/mesh.cpp \
    core/gl/fps.cpp \
    core/gl/inputregister.cpp \
    core/main_controller.cpp \
    dialogs/about/about.cpp \
    renderer/baserenderer.cpp \
    renderer/pipeline.cpp \
    renderer/fbxrenderer.cpp \
    assets/meshasset.cpp \
    assets/assetloader.cpp \
    utils/math.cpp \
    core/projectmanager.cpp \
    utils/json.cpp \
    script_module/gameobject.cpp \
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
    fbx_manager/mesh/mesh_material_loader.cpp \
    fbx_manager/mesh/loader/fbx_geometryloader.cpp \
    fbx_manager/mesh/loader/fbx_materialloader.cpp \
    fbx_manager/material/fbx_material.cpp \
    fbx_manager/mesh/serialize_aaem.cpp \
    opengl_worker/aaeopenglworkerthread.cpp \
    opengl_worker/workerthread.cpp \
    core/gl/aux_glcontroller.cpp \
    material/material.cpp \
    opengl_worker/baseworkerthread.cpp \
    opengl_worker/workerthread2.cpp \
    core/globalsettings.cpp \
    texture/texture.cpp



HEADERS  += \
    core/gl/glcontroller.hpp \
    dialogs/console/console.hpp \
    script_module/scriptengine.hpp \
    dialogs/console/logger.hpp \
    fbx_manager/fbxmanager.hpp \
    fbx_manager/entry/meshentry.hpp \
    fbx_manager/mesh/mesh.hpp \
    core/gl/fps.hpp \
    core/gl/inputregister.hpp \
    core/main_controller.hpp \
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
    fbx_manager/mesh/loader/fbx_materialloader.hpp \
    fbx_manager/mesh/loader/fbx_geometryloader.hpp \
    fbx_manager/material/fbx_material.hpp \
    aae_defines.hpp \
    opengl_worker/aaeopenglworkerthread.hpp \
    opengl_worker/workerthread.hpp \
    utils/bounding_box.hpp \
    utils/gl_util.hpp \
    material/material.hpp \
    opengl_worker/baseworkerthread.hpp \
    opengl_worker/workerthread2.hpp \
    core/globalsettings.hpp \
    texture/texture.hpp




FORMS    += core/controller.ui \
    dialogs/console/console.ui \
    dialogs/about/about.ui \
    dialogs/mesh_import_dialog/meshimport.ui




CONFIG += c++11





RESOURCES += \
    resources.qrc





LIBS += -lfbxsdk















